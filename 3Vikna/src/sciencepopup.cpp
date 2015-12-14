#include "../include/sciencepopup.h"
#include "ui_sciencepopup.h"
#include <QTableWidget>
#include "../include/gui.h"
#include "ui_gui.h"
//#include <QMediaPlayer>

sciencePopUp::sciencePopUp(QWidget *parent, GUI* daddyCool) :
    QDialog(parent),
    ui(new Ui::sciencePopUp)
{
    ui->setupUi(this);
    Parent = daddyCool;

    //Sets the order of things that are selected when 'tab' is pressed.
    setTabOrder(ui->field1, ui->field2);
    setTabOrder(ui->field2, ui->field3);
    setTabOrder(ui->field3, ui->field4);
    setTabOrder(ui->field4, ui->field5);
    setTabOrder(ui->field5, ui->field6);
    setTabOrder(ui->field6, ui->buttonBox);
    setTabOrder(ui->buttonBox, ui->field1);

    ui->field3->setMinimumDate(QDate(101, 1, 1));
    ui->field4->setMinimumDate(QDate(102, 1, 1));

    /*QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/new/audio/ping.wav"));
    music->play();*/
}

sciencePopUp::~sciencePopUp()
{
    delete ui;
}

//When the "OK" button is pressed.
void sciencePopUp::on_buttonBox_accepted()
{
    //Reads the string in each field.
     QString myField1 = ui->field1->toPlainText();
     QString myField2 = ui->field2->currentText();
     QString myField3 = ui->field3->text();
     QString myField4 = ui->field4->text();
     QString myField5 = ui->field5->toPlainText();
     QString myField6 = ui->field6->toPlainText();

     if(myField1 != "" && myField3<myField4)
     {
         Parent->AddToTable(myField1, myField2, myField3, myField4, myField5, myField6);
     }
     else Parent->ErrorMessage();
}
