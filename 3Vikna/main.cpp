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
    QSqlQuery query = db.exec(QString("Select * from Scientists;"));
    QSqlError err = query.lastError();
    cout << err.text().toStdString() << endl;
    while(query.next())
    {
        if(query.value(2).toString().toStdString().length() > 0) //Just an idea of how the output could look. Please take a look and see what you like.
        {
            cout << "Full name: " << query.value(1).toString().toStdString() + " "
                 << query.value(2).toString().toStdString() + " "
                 << query.value(3).toString().toStdString() << endl;
        }
        else
        {
            cout << "Full name: " << query.value(1).toString().toStdString() + " "
                 << query.value(3).toString().toStdString() << endl;
        }
        cout << "Gender: " <<  query.value(4).toString().toStdString() << endl
             << "Year of birth: " <<  query.value(5).toString().toStdString() << endl
             << "Year of death: " <<  query.value(6).toString().toStdString() << endl
             << "Nationality: " <<  query.value(7).toString().toStdString() << endl
             << "Field of work: " <<  query.value(8).toString().toStdString() << endl << endl
             << "--------------------------------------------------------------"<< endl << endl;
    }

    return 0;
}



/*<< "First name: " << query.value(1).toString().toStdString() << endl
  << "Middle name: " <<  query.value(2).toString().toStdString() << endl
  << "Last name: " <<  query.value(3).toString().toStdString() << endl */
