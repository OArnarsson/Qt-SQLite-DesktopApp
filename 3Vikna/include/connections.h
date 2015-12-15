#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include "gui.h"
#include <QDialog>
#include <QList>
#include <QListWidgetItem>


namespace Ui {
class Connections;
}

class Connections : public QDialog
{
    Q_OBJECT

public:
    explicit Connections(GUI *parent = 0,MagicalDataClass* dataThief = 0);
    ~Connections();

private slots:
    void on_OkButton_2_clicked();

    void on_OkButton_clicked();

    void on_quicksearch_returnPressed();

    void on_Left_itemClicked(QListWidgetItem *item);

    void on_comboBox_currentIndexChanged(int index);

    void on_Remove_clicked();

private:
    Ui::Connections *ui;
    GUI* daddy;
    MagicalDataClass* dataLayer;
    void addTable(ComputerScientist compsci);
    void addTable(computer compsci);
    computer parseComputer(string term);
    ComputerScientist parseScientist(string term);
};

#endif // CONNECTIONS_H
