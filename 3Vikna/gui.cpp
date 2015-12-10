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
}


GUI::~GUI()
{
    delete ui;
}

void GUI::on_Table_cellChanged(int row, int column)
{
    QMessageBox box;
    box.setText("OMYGODYOU'REEDITINGSHIT!");
    box.exec();
}

void GUI::on_Add_clicked()
{

    /*ui->Table->setRowCount(2);
    ui->Table->setColumnCount(4);
    ui->Table->setItem(0, 0, new QTableWidgetItem("Hello"));*/
    Dialog addPopUp;
    addPopUp.setModal(true);
    addPopUp.exec();
}

void GUI::on_Remove_clicked()
{
     (*MyDataLayer).remove(ComputerScientist());
}

void GUI::on_Table_clicked(const QModelIndex &index)
{

}

void GUI::on_Fostudagur_clicked()
{
    QString link = "http://erfostudagur.is/";
    QDesktopServices::openUrl(QUrl(link));
}
