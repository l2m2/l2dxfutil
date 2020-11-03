#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include "../dxf2gerber/l2_dxf2gerber.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (argc >= 2) {
        QString dxf_path = argv[1];
        if (!QFile::exists(dxf_path)) {
            qFatal("The specified path does not exist.");
            return 1;
        }
        QFileInfo finfo(dxf_path);
        QString err;
        qInfo() << finfo.absoluteFilePath() << finfo.absoluteDir().absolutePath();
        bool ok = L2_Dxf2Gerber::toDir(finfo.absoluteFilePath(), finfo.absoluteDir().absolutePath(), &err);
        if (!ok) {
            qFatal("Convert failed. Error: %s", err.toLatin1().constData());
            return 1;
        }
    }

    return 0;
}
