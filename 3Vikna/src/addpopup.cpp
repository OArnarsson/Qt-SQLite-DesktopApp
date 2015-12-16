#include "../include/addpopup.h"
#include "ui_addpopup.h"
#include "include/computer.h"
#include <iostream>
#include <QTableWidget>
#include <QMediaPlayer>
#include "../include/gui.h"
#include "ui_gui.h"
#include <sstream>

/*****************************
 * constructing constructors
 * *******************************/
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

    this->setFixedSize(192,341);

    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/new/audio/ping.wav"));
    music->play();
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
         if(editing.field(1).size() < 1 && editing.field(2).size()<1)
         {
            Parent->AddToTable(myField1, myField2, myField3, myField4, myField5);
         }
         else
         {
             Parent->change(myField1,myField2,myField3,myField4,myField5);
         }
     }
     else Parent->ErrorMessage();

}
/***************************************
 * mode
 * changes add mode to editing mode
 * ***********************************/
void Dialog::mode(computer newMode)
{
    editing = newMode;
    ui->field1->document()->setPlainText(QString::fromStdString(editing.field(1)));
    ui->field3->setCurrentIndex((editing.field(3) == "Mechanical computer") ? 0:((editing.field(3) == "Transistorized") ? 1:2));
    ui->field4->setCurrentIndex((editing.field(4) == "true") ? 0:1);
    stringstream S;
    S << editing.field(2);
    int I;
    S >> I;
    ui->field2->setDate(QDate(I,1,1));
    ui->field5->document()->setPlainText(QString::fromStdString(editing.field(5)));
}
