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
    /*UI ui;
    ui.start();*/
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    cout << db.isValid();
    QString lol = "LLLLL";
    db.setDatabaseName(lol);
    return 0;
}
