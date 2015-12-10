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

//When the "OK" button is pressed.
void Dialog::on_buttonBox_accepted()
{
    //Reads the string in each field.
     QString myField1 = ui->field1->toPlainText();
     QString myField2 = ui->field2->toPlainText();
     QString myField3 = ui->field3->toPlainText();
     QString myField4 = ui->field4->toPlainText();
     QString myField5 = ui->field5->toPlainText();

     //Debug to print them out
     std::cout << myField1.toStdString() << endl;
     std::cout << myField2.toStdString() << endl;
     std::cout << myField3.toStdString() << endl;
     std::cout << myField4.toStdString() << endl;
     std::cout << myField5.toStdString() << endl;
}
