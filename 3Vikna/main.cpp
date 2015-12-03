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
    QString lol = "CompDataBase.sqlite";
    db.setDatabaseName(lol);
    cout << db.open() << endl;
    QSqlQuery query = db.exec(QString("Select * from Computerscientists;"));
    QSqlError err = query.lastError();
    cout << err.text().toStdString() << endl;
    while(query.next()){
        cout << query.value(2).toString().toStdString() << endl;
    }

    return 0;
}
