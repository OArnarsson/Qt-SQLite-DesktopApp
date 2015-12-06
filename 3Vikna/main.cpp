#include "include/ComputerScientist.h"
#include "include/FileData.h"
#include "include/ui.h"
#include <iostream>
#include <string>
#include "include/dbtest.h"
#include <QtSql>
using namespace std;

int main()
{
   /* UI ui;
    ui.start();*/
    FileData files("CompDataBase.sqlite");
    ComputerScientist tt("test","s","isgood","Male","1943","1978","Irish","Deead");
    files.Add(tt);
}



/*<< "First name: " << query.value(1).toString().toStdString() << endl
  << "Middle name: " <<  query.value(2).toString().toStdString() << endl
  << "Last name: " <<  query.value(3).toString().toStdString() << endl */
