#ifndef GUI_H
#define GUI_H

#include <QMainWindow>

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

private:
    Ui::GUI *ui;
};

#endif // GUI_H
