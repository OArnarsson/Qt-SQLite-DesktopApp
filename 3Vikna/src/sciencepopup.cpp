#include "../include/sciencepopup.h"
#include "ui_sciencepopup.h"
#include <QTableWidget>
#include <QMediaPlayer>
#include "../include/gui.h"
#include "ui_gui.h"
#include <sstream>
//#include <QMediaPlayer>

/*****************************
 * consructing
 * ****************************/
sciencePopUp::sciencePopUp(QWidget *parent, GUI* daddyCool) :
    QDialog(parent),
    ui(new Ui::sciencePopUp)
{
    ui->setupUi(this);
    Parent = daddyCool;
    editing = ComputerScientist();

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

    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/new/audio/ping.wav"));
    music->play();

    this->setFixedSize(192,401);
}

sciencePopUp::~sciencePopUp()
{
    delete ui;
}

/*********************************************
 * When the "OK" button is pressed.
 * parses the information given
 *  calls dad to add it to table
 * *******************************************/
void sciencePopUp::on_buttonBox_accepted()
{
     //Reads the string in each field.
     QString myField1 = ui->field1->toPlainText();
     QString myField2 = ui->field2->currentText();
     QString myField3 = ui->field3->text();
     QString myField4 = ui->field4->text();
     QString myField5 = ui->field5->toPlainText();
     QString myField6 = ui->field6->toPlainText();

     if(myField4 == "2015")
     {
         myField4 = "";
     }
     if(myField1 != "")
     {
         if(myField4 == "" || myField4 > myField3)
         {
             if(editing.field(1).size() < 1 && editing.field(2).size() < 1 && editing.field(3).size() < 1)
             {
                 Parent->AddToTable(myField1, myField2, myField3, myField4, myField5, myField6);
             }
             else
             {
                 Parent->change(myField1,myField2,myField3,myField4,myField5,myField6);
             }
         }
         else
         {
             cout << 79;
            Parent->ErrorMessage();
         }
     }
     else
     {
         Parent->ErrorMessage();
         cout << 86;
     }

}

/*********************************
 * mode
 * changes this add dialogue to edit dialogue
 * **********************************/
void sciencePopUp::mode(ComputerScientist newMode)
{
    editing = newMode;
    ui->field1->document()->setPlainText(QString::fromStdString(editing.field(1) + " " + editing.field(2) + " " + editing.field(3)));
    ui->field2->setCurrentIndex((editing.field(4) == "Male") ? 0:1);
    stringstream S;
    S << editing.field(5);
    int I;
    S >> I;
    ui->field3->setDate(QDate(I,1,1));
    S.clear();
    if(editing.field(6).size() >= 1)
    {
        S << editing.field(6);
        S >> I;
    }
    else
    {
        I = 2015;
    }
    ui->field4->setDate(QDate(I,1,1));
    ui->field5->document()->setPlainText(QString::fromStdString(editing.field(7)));
    ui->field6->document()->setPlainText(QString::fromStdString(editing.field(8)));
}
