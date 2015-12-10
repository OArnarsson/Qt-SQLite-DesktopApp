#include "addpopup.h"
#include "ui_addpopup.h"
#include "include/computer.h"
#include <iostream>

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

void Dialog::on_field1_textChanged()
{
    QString myField1 = ui->field1->toPlainText();
    std::cout << myField1.toStdString();
}
