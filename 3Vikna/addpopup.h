#ifndef ADDPOPUP_H
#define ADDPOPUP_H

#include <QDialog>
#include "gui.h"
#include "ui_gui.h"

namespace Ui
{
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0, GUI* daddyCool = NULL);
    ~Dialog();

private slots:

    void on_buttonBox_accepted();

private:
    Ui::Dialog *ui;
    GUI* Parent;
};

#endif // ADDPOPUP_H
