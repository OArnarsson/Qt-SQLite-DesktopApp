#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <algorithm>
#include <vector>
#include "../include/FileData.h"
#include <regex>
#include "../include/ComputerScientist.h"

void sanitize(string* String){
    for(unsigned int j = 0; j < (*String).size();j++){
        if((*String)[j] == ',' || (*String)[j] == '"' || (*String)[j] == ';'){
            (*String)[j] = ' ';
        }
    }
}

bool isNumber(string num){
    return regex_match(num,regex("[(-|+)|][0-9]+"));
}

const string DEFAULT_YEAR = "-2015";
const int NUMBER_OF_COLUMNS = 6;
//Constructor.
//Reads from the database on the file (if exists)
FileData::FileData(string DataBaseFile){
     base = DataBaseFile;
     valid = open();
     if(valid){
         Load();
     }
}

bool FileData::open(){
    connection = QSqlDatabase::addDatabase("QSQLITE");
    connection.setDatabaseName(QString::fromStdString(base));
    bool success = connection.open();
    return success;
}

//Add
//Accepts a ComputerScientist class
//Stores it in memory until ready to write to disk
bool FileData::Add(ComputerScientist scientist){
     if(valid){
         string info[8];
         for(int i = 0; i < 8; i++){
             info[i] = scientist.field(i);
             sanitize(&info[i]);
         }
         QSqlQuery query(connection);
         query.prepare("INSERT INTO SCIENTISTS(FirstName,MiddleName,LastName,Gender,YearOfBirth,YearOfDeath,Nationality,Field) "
                       "VALUES (?,?,?,?,?,?,?,?);");
         for(int i = 0; i < 8; i++){
             if(info[i] == ""){
                 info[i] = "NULL";
             }
             if(i >= 5 && i < 7){
                 if(!isNumber(info[i])){
                     info[i] = "NULL";
                 }
             }
            query.bindValue(i,QString::fromStdString(info[i]));
         }
         query.exec();
         return(query.lastError().text().size() < 2);
     }
     else{
         valid = open();
         if(valid){
             Add(scientist);
             return true;
         }
         return false;
     }
}


//Load()
//Reads all entries from the database
//Returns true if opening the database worked
//Writes out to Stdout how many entries were loaded for debugging purposes
bool FileData::Load(string filename){
    if(!valid) cout << "ERROR!";
    QSqlQuery query(connection);
    query.prepare("SELECT"
                  "(SELECT COUNT(DISTINCT ID) FROM Scientists),"
                 "(SELECT COUNT(DISTINCT ID) FROM Computers),"
                  "(SELECT COUNT(DISTINCT ScientistID) FROM Owners)");
     //Done. Report success
    query.exec();
    query.first();
    if(query.lastError().text().size() > 2){
        cout << query.lastError().text().toStdString() << endl;
        return false;
    }
    else{
        cout << query.value(0).toString().toStdString() << " Scientists loaded from database" << endl;
        cout << query.value(1).toString().toStdString() << " Computers loaded from database" << endl;
        cout << query.value(2).toString().toStdString() << " Connectons loaded from database" << endl;
         return true;
    }
}

vector<string> FileData::explode(const string s, char delim){
     vector<string> ret;
     stringstream stream(s);
     string temp;
     while(getline(stream, temp, delim)){
          ret.push_back(temp);
     }
     return ret;
}

vector<ComputerScientist> FileData::DataSet(){
    return vector<ComputerScientist>();
}
