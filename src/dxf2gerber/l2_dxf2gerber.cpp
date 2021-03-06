#include "l2_dxf2gerber.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QScopedPointer>
#include <QUuid>
#include "../dxflib/dl_dxf.h"
#include "l2_dxfadapter.h"

static void write(const QString &layer, const QVariantList &data, QTextStream &out)
{
    QMap<QString, int> devices;
    for (auto obj : data) {
        QVariantMap objMap = obj.toMap();
        if (objMap.contains("device")) {
            devices.insert(objMap.value("device").toString(), 0);
        }
    }

    out << "%FSLAX36Y36*%\n";
    out << "%MOMM*%\n";
    out << "%LN" << layer << "*%\n";

    int counter = 10;
    for (auto d : devices.keys()) {
        out << "%ADD" << counter << d << "%\n";
        devices[d] = counter;
        counter += 1;
    }

    QString current_device;
    for (auto obj : data) {
        QVariantMap objMap = obj.toMap();
        if (objMap.contains("command")) {
            out << objMap.value("command").toString() << "\n";
        } else {
            QString device = objMap.value("device").toString();
            if (device != current_device) {
                out << "G54D" << devices[device] << "*\n";
                current_device = device;
            }
            QString line("");
            if (objMap.contains("mode")) {
                line.append(objMap.value("mode").toString());
            }
            if (objMap.contains("x")) {
                line.append(QString("X%1").arg(qRound(objMap.value("x").toDouble() * 1000000)));
            }
            if (objMap.contains("y")) {
                line.append(QString("Y%1").arg(qRound(objMap.value("y").toDouble() * 1000000)));
            }
            if (objMap.contains("i")) {
                line.append(QString("I%1").arg(qRound(objMap.value("i").toDouble() * 1000000)));
            }
            if (objMap.contains("j")) {
                line.append(QString("J%1").arg(qRound(objMap.value("j").toDouble() * 1000000)));
            }
            if (objMap.contains("style")) {
                line.append(objMap.value("style").toString());
            }
            out << line << "*\n";
        }
    }

    out << "M02*\n";
}

bool L2_Dxf2Gerber::toDir(const QString &dxfPath, const QString &gerberDir, QString *err)
{
    if (!QFile::exists(dxfPath)) {
        *err = "DXF file does not exist.";
        return false;
    }
    QScopedPointer<DL_Dxf> dxf(new DL_Dxf());
    QScopedPointer<L2_DxfAdapter> adapter(new L2_DxfAdapter());
    bool ok = dxf->in(std::string(dxfPath.toLocal8Bit()), adapter.data());
    if (ok) {
        QMap<QString, QVariantList> layers = adapter->getLayers();
        if (layers.isEmpty()) {
            *err = QString("no layer.");
            return false;
        }
        QDir dir(gerberDir);
        if (!dir.exists()) {
            if (!dir.mkpath(gerberDir)) {
                *err = QString("mkpath(%1) failed.").arg(gerberDir);
                return false;
            }
        }
        QMap<QString, QVariantList>::const_iterator it;
        for (it = layers.constBegin(); it != layers.constEnd(); it++) {
            QString filename = gerberDir + QDir::separator() + it.key() + ".gbr";
            QFile file;
            file.setFileName(filename);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                *err = QString("open file(%1) failed.").arg(filename);
                return false;
            }

            QTextStream out(&file);
            write(it.key(), it.value(), out);
            file.close();
        }
    }
    return ok;
}
