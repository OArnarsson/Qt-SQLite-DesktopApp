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
    explicit GUI(QWidget *parent = 0);
    ~GUI();

private slots:
    void on_Table_cellChanged(int row, int column);

    void on_Add_clicked();

    void on_Remove_clicked();

    void on_Table_clicked(const QModelIndex &index);

private:
    Ui::GUI *ui;
    MagicalDataClass* MyDataLayer;
};

#endif // GUI_H
