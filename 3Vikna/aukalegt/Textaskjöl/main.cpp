#include "include/ComputerScientist.h"
#include "include/FileData.h"
#include "include/ui.h"
#include <iostream>
#include <string>
#include <QtSql>



int main()
{
   UI ui;
    ui.start();
    FileData F("CompDataBase.sqlite");
    ComputerScientist one("Alan","","Turing","","","","","");
    computer two("Turing","1936","Transistorized");
    F.addConnection(one,two);
}
