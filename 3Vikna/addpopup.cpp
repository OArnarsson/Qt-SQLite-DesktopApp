#include "addpopup.h"
#include "ui_addpopup.h"
#include "include/computer.h"
#include <iostream>
#include <QTableWidget>
#include "gui.h"
#include "ui_gui.h"

Dialog::Dialog(QWidget *parent, GUI* daddyCool) :
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

     Parent->AddToTable(myField1, myField2, myField3, myField4, myField5);
}
