#include "gui.h"
#include "ui_gui.h"
#include <QMessageBox>

GUI::GUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GUI)
{
    ui->setupUi(this);
}

GUI::~GUI()
{
    delete ui;
}


void GUI::on_pushButton_clicked()
{
    ui->Table->setRowCount(2);
    ui->Table->setColumnCount(4);
    ui->Table->setItem(0, 0, new QTableWidgetItem("Hello"));
}

void GUI::on_Table_cellChanged(int row, int column)
{
    QMessageBox box;
    box.setText("OMYGODYOU'REEDITINGSHIT!");
    box.exec();
}
