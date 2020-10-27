#include <QCoreApplication>
#include <QDebug>
#include "l2_dxf2odb.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString err;
    bool ok = L2_Dxf2Odb::run("E:/demo.dxf", "E:/demo.odb", &err);
    if (!ok) {
        qDebug() << "Error: " << err;
        qApp->quit();
    }
    qDebug() << "Fuck Me.";
    return 0;
}
