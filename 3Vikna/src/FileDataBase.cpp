#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <algorithm>
#include <vector>
#include "../include/FileData.h"
#include "../include/ComputerScientist.h"
#include "../include/computer.h"

const string DEFAULT_YEAR = "-2015";
const int NUMBER_OF_COLUMNS = 6;


//********************************************
//sanitize(string pointer)
//Removes "," , ";", and "'" from input to make a very crude and primitive escape string
//We don't want SQL injections, now do we?
//********************************************
void sanitize(string* String){
    for(unsigned int j = 0; j < (*String).size();j++){
        if((*String)[j] == ',' || (*String)[j] == '"' || (*String)[j] == ';'){
            (*String)[j] = ' ';
        }
    }
}

//********************************************
// IsNumber....does exactly what you'd expect,
//Takes string, returns if it's a positive integer
//********************************************
bool isNumber(string num){
    for(unsigned int i = 0; i < num.size(); i++){
        if(!isdigit(num[i])){
            return false;
        }
    }
    return true;
}

//****************************************
//Constructor.
//Reads from the database on the file (if exists)
//***************************************
FileData::FileData(string DataBaseFile){
     base = DataBaseFile;
     valid = open();
     if(valid){
         Load();
     }
}

//********************************************
//open()
//Establishes a connection to the SQL database
//Returns true on success
//********************************************
bool FileData::open(){
    connection = QSqlDatabase::addDatabase("QSQLITE");
    connection.setDatabaseName(QString::fromStdString(base));
    bool success = connection.open();
    return success;
}

//*******************************************
//Add(ComputerScientist
//Accepts a ComputerScientist class
//Stores it in SQL database
//*******************************************
bool FileData::Add(ComputerScientist scientist){
     if(valid){
         string info[8];
         for(int i = 0; i < 8; i++){
             info[i] = scientist.field(i+1);
             sanitize(&info[i]);
         }
         QSqlQuery query(connection);
         query.prepare("INSERT INTO Scientists(FirstName,MiddleName,LastName,Gender,YearOfBirth,YearOfDeath,Nationality,Field) "
                       "VALUES (?,?,?,?,?,?,?,?);");
         for(int i = 0; i < 8; i++){
             if(info[i] == ""){
                 info[i] = "NULL";
             }
             if(i >= 4 && i < 6){
                 if(!isNumber(info[i])){
                     info[i] = "NULL";
                 }
             }
            query.bindValue(i,QString::fromStdString(info[i]));
         }
         query.exec();
         cout << "HERE" << endl;
         cout << query.lastError().text().toStdString() << endl;
         return(query.lastError().text().size() < 2);
     }
     else{
         cout << "INVALID"<<endl;
         valid = open();
         if(valid){
             Add(scientist);
             return true;
         }
         return false;
     }
}
//*********************************
// Add(Computer comp
// Takes information from a computer class and enters into the SQL database
//*********************************

bool FileData::Add(computer mycomp){
     if(valid){
         string info[8];
         for(int i = 0; i < 8; i++){
             info[i] = mycomp.field(i+1);
             sanitize(&info[i]);
         }
         QSqlQuery query(connection);
         query.prepare("INSERT INTO Computers(Name,Year,Type,Built,Location)"
                       "VALUES (?,?,?,?,?);");
         for(int i = 0; i < 5; i++){
             if(info[i] == ""){
                 info[i] = "NULL";
             }
             if(i == 1){
                 if(!isNumber(info[i])){
                     info[i] = "NULL";
                 }
             }
            query.bindValue(i,QString::fromStdString(info[i]));
         }
         query.exec();
         cout << "HERE" << endl;
         cout << query.lastError().text().toStdString() << endl;
         return(query.lastError().text().size() < 2);
     }
     else{
         cout << "INVALID"<<endl;
         valid = open();
         if(valid){
             Add(mycomp);
             return true;
         }
         return false;
     }
}

//****************************************************************
//Load()
//Reads all entries from the database
//Returns true if opening the database worked
//Writes out to Stdout how many entries were loaded for debugging purposes
//****************************************************************
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

//****************************************************************
//Explode()
//takes a string and delimeter.
//Breaks the substrings into a vector grouped by delimiter
//****************************************************************
vector<string> FileData::explode(const string s, char delim){
     vector<string> ret;
     stringstream stream(s);
     string temp;
     while(getline(stream, temp, delim)){
          ret.push_back(temp);
     }
     return ret;
}

//****************************************************************
//Returns everything in the database
//Mode = 0: returns all computerscientists
//Mode = 1: Returns all computers
//Mode = 2: Returns all connections
//****************************************************************
vector<ComputerScientist> FileData::DataSet(int mode = 0){
    mode++;
    return vector<ComputerScientist>();
}
