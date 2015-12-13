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
    void ErrorMessage();
    ~GUI();

private slots:

    void on_Add_clicked();

    void on_Remove_clicked();

    void on_Fostudagur_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_searchbar_returnPressed();

private:
    Ui::GUI *ui;
    MagicalDataClass* MyDataLayer;
    void searchCompSci();
    void searchComputer();
    ComputerScientist getRowScientist(int rown);
    computer getRowComputer(int rown);
};

#endif // GUI_H
