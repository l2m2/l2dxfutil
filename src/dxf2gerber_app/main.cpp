#include <QCoreApplication>
#include <QDebug>
#include "../dxf2gerber/l2_dxf2gerber.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString err;
    bool ok = L2_Dxf2Gerber::run("E:/01.dxf", "E:/", &err);
    if (!ok) {
        qDebug() << "Error: " << err;
        qApp->quit();
    }
    qDebug() << "Fuck Me.";
    return 0;
}
