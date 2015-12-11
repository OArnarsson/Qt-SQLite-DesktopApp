#include "sciencepopup.h"
#include "ui_sciencepopup.h"
#include <QTableWidget>
#include "gui.h"
#include "ui_gui.h"

sciencePopUp::sciencePopUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sciencePopUp)
{
    ui->setupUi(this);

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
}

sciencePopUp::~sciencePopUp()
{
    delete ui;
}
