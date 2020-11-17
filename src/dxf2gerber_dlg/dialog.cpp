#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include "../dxf2gerber/l2_dxf2gerber.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Select DXF", "", "DXF(*.dxf)");
    qDebug() << __FUNCTION__ << filename;
    if (filename.isEmpty()) {
        return;
    }
    ui->lineEdit->setText(filename);
    QFileInfo info(filename);
    QString err;
    bool ok = L2_Dxf2Gerber::toDir(filename, info.absoluteDir().absolutePath(), &err);
    if (!ok) {
        QMessageBox::warning(this, "Convert failed!", err);
        return;
    }
    QMessageBox::information(this, "Infomation", "Done!");
}
