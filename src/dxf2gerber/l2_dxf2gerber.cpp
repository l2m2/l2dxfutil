#include "l2_dxf2gerber.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include "../dxflib/dl_dxf.h"
#include "l2_dxfadapter.h"

bool L2_Dxf2Gerber::run(const QString &dxfPath, const QString &gerberDir, QString *err)
{
    if (!QFile::exists(dxfPath)) {
        *err = "DXF file does not exist.";
        return false;
    }
    DL_Dxf *dxf = new DL_Dxf();
    L2_DxfAdapter *adapter = new L2_DxfAdapter();
    bool ok = dxf->in(dxfPath.toStdString(), adapter);
    if (ok) {
        QDir dir(gerberDir);
        if (!dir.exists()) {
            if (!dir.mkpath(gerberDir)) {
                *err = QString("mkpath(%1) failed.").arg(gerberDir);
                return false;
            }
        }
        QMap<QString, QVariantList> layers = adapter->getLayers();
        QMap<QString, QVariantList>::const_iterator it;
        for (it = layers.constBegin(); it != layers.constEnd(); it++) {
            QString filename = gerberDir + QDir::separator() + it.key() + ".gbr";
            QFile file;
            file.setFileName(filename);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                *err = QString("open file(%1) failed.").arg(filename);
                return false;
            }

            QMap<QString, int> devices;
            for (auto obj : it.value()) {
                QVariantMap objMap = obj.toMap();
                if (objMap.contains("device")) {
                    devices.insert(objMap.value("device").toString(), 0);
                }
            }

            QTextStream out(&file);
            out << "%FSLAX36Y36*%\n";
            out << "%MOMM*%\n";
            out << "%LN" << it.key() << "*%\n";

            int counter = 10;
            for (auto d : devices.keys()) {
                out << "%ADD" << counter << d << "%\n";
                devices[d] = counter;
                counter += 1;
            }

            QString current_device;
            for (auto obj : it.value()) {
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
                        line.append(QString("X%1").arg(static_cast<int>(objMap.value("x").toDouble() * 1000000)));
                    }
                    if (objMap.contains("y")) {
                        line.append(QString("Y%1").arg(static_cast<int>(objMap.value("y").toDouble() * 1000000)));
                    }
                    if (objMap.contains("i")) {
                        line.append(QString("I%1").arg(static_cast<int>(objMap.value("i").toDouble() * 1000000)));
                    }
                    if (objMap.contains("j")) {
                        line.append(QString("J%1").arg(static_cast<int>(objMap.value("j").toDouble() * 1000000)));
                    }
                    if (objMap.contains("style")) {
                        line.append(objMap.value("style").toString());
                    }
                    out << line << "*\n";
                }
            }

            out << "M02*\n";
            file.close();
        }
    }
    return ok;
}
