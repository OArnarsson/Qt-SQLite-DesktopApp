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
    Parent = daddyCool;

    //Sets the order of things that are selected when 'tab' is pressed.
    setTabOrder(ui->field1, ui->field2);
    setTabOrder(ui->field2, ui->field3);
    setTabOrder(ui->field3, ui->field4);
    setTabOrder(ui->field4, ui->field5);
    setTabOrder(ui->field5, ui->buttonBox);
    setTabOrder(ui->buttonBox, ui->field1);

    ui->field2->setMinimumDate(QDate(101, 1, 1));
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
     QString myField2 = ui->field2->text();
     QString myField3 = ui->field3->currentText();
     QString myField4 = ui->field4->currentText();
     QString myField5 = ui->field5->toPlainText();

     if(myField1 != "")
     {
         Parent->AddToTable(myField1, myField2, myField3, myField4, myField5);
     }
     else Parent->ErrorMessage();

}
