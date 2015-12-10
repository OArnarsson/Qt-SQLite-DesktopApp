#include "gui.h"
#include "ui_gui.h"
#include <iostream>
#include <QMessageBox>

GUI::GUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GUI)
{
    ui->setupUi(this);
    std::cout << "HEYLLO";
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

    ui->Table->setRowCount(2);
    ui->Table->setColumnCount(4);
    ui->Table->setItem(0, 0, new QTableWidgetItem("Hello"));
}
