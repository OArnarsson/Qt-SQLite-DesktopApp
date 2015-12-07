#include "include/ComputerScientist.h"
#include "include/FileData.h"
#include "include/ui.h"
#include <iostream>
#include <string>
#include <QtSql>



int main()
{
   /* UI ui;
    ui.start();*/
    FileData files("CompDataBase.sqlite");
    ComputerScientist tt("test","s","isgood","Male","1943","1978","Irish","Deead");
    files.Add(tt);
}
