#include "gui.h"
#include "ui_gui.h"
#include <iostream>
#include <QMessageBox>
#include <QDesktopServices>
#include "include/ComputerScientist.h"
#include "include/magicaldataclass.h"
#include "include/computer.h"
#include "addpopup.h"

GUI::GUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GUI)
{
    ui->setupUi(this);
    MyDataLayer = new MagicalDataClass("CompDataBase.sqlite");

    ui->mainTable->setRowCount(1);
    ui->mainTable->setColumnCount(5);
    ui->mainTable->setItem(0, 0, new QTableWidgetItem("Hello"));

    ui->statusBar->showMessage("Ludwig van Beethoven was a German composer from the late 18th century.", 2000);
}


GUI::~GUI()
{
    delete ui;
}


void GUI::on_Add_clicked()
{
    Dialog addPopUp;
    addPopUp.setModal(true);
    addPopUp.exec();
}

void GUI::on_Remove_clicked()
{
     (*MyDataLayer).remove(ComputerScientist());
}

void GUI::on_Fostudagur_clicked()
{
    QString link = "http://erfostudagur.is/";
    QDesktopServices::openUrl(QUrl(link));
}

void GUI::AddToTable(QString field1,QString field2, QString field3, QString field4, QString field5)
{
    ui->mainTable->setRowCount(ui->mainTable->rowCount()+1);
    ui->mainTable->setItem(ui->mainTable->rowCount()-1,0, new QTableWidgetItem(field1));
    ui->mainTable->setItem(ui->mainTable->rowCount()-1,1, new QTableWidgetItem(field2));
    ui->mainTable->setItem(ui->mainTable->rowCount()-1,2, new QTableWidgetItem(field3));
    ui->mainTable->setItem(ui->mainTable->rowCount()-1,3, new QTableWidgetItem(field4));
    ui->mainTable->setItem(ui->mainTable->rowCount()-1,4, new QTableWidgetItem(field5));
}
