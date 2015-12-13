#include "../include/gui.h"
#include "include/FileData.h"
#include "include/ComputerScientist.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GUI w;
    w.show();
    return a.exec();
}
