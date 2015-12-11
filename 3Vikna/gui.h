#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include "include/ComputerScientist.h"
#include "include/magicaldataclass.h"
#include "include/computer.h"

namespace Ui {
class GUI;
}

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    void AddToTable(QString field1,QString field2, QString field3, QString field4, QString field5);
    explicit GUI(QWidget *parent = 0);
    ~GUI();

private slots:

    void on_Add_clicked();

    void on_Remove_clicked();

    void on_Fostudagur_clicked();

private:
    Ui::GUI *ui;
    MagicalDataClass* MyDataLayer;
};

#endif // GUI_H
