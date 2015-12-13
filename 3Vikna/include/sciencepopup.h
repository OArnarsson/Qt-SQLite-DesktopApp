#ifndef SCIENCEPOPUP_H
#define SCIENCEPOPUP_H

#include <QDialog>
#include "gui.h"
#include "ui_gui.h"

namespace Ui {
class sciencePopUp;
}

class sciencePopUp : public QDialog
{
    Q_OBJECT

public:
    explicit sciencePopUp(QWidget *parent = 0, GUI* daddyCool = NULL);
    ~sciencePopUp();

private slots:

    void on_buttonBox_accepted();

private:
    Ui::sciencePopUp *ui;
    GUI* Parent;
};

#endif // SCIENCEPOPUP_H
