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
void sanitize(string* String)
{
    for(unsigned int j = 0; j < (*String).size();j++)
    {
        if((*String)[j] == ',' || (*String)[j] == '"' || (*String)[j] == ';')
        {
            (*String)[j] = ' ';
        }
    }
}

//********************************************
// IsNumber....does exactly what you'd expect,
//Takes string, returns if it's a positive integer
//********************************************
bool isNumber(string num)
{
    for(unsigned int i = 0; i < num.size(); i++)
    {
        if(!isdigit(num[i]))
        {
            return false;
        }
    }
    return true;
}

//****************************************
//Constructor.
//Reads from the database on the file (if exists)
//***************************************
FileData::FileData(string DataBaseFile)
{
     base = DataBaseFile;
     valid = open();
     if(valid)
     {
         cout << "ISTHISLOADINGYET!!!!";
         Load();
     }
}

//********************************************
//open()
//Establishes a connection to the SQL database
//Returns true on success
//********************************************
bool FileData::open()
{
    connection = QSqlDatabase::addDatabase("QSQLITE");
    connection.setDatabaseName(QString::fromStdString(base));
    bool success = connection.open();
    if(success){
        cout << "WOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO";
    }
    return success;
}

//*******************************************
//Add(ComputerScientist
//Accepts a ComputerScientist class
//Stores it in SQL database
//*******************************************
bool FileData::Add(ComputerScientist scientist)
{
     if(valid)
     {
         string info[8];
         for(int i = 0; i < 8; i++)
         {
             info[i] = scientist.field(i+1);
             sanitize(&info[i]);
         }
         QSqlQuery query(connection);
         query.prepare("INSERT INTO Scientists(FirstName,MiddleName,LastName,Gender,YearOfBirth,YearOfDeath,Nationality,Field) "
                       "VALUES (?,?,?,?,?,?,?,?);");
         for(int i = 0; i < 8; i++)
         {
            query.bindValue(i,QString::fromStdString(info[i]));
         }
         query.exec();
         cout << "HERE" << endl;
         cout << query.lastError().text().toStdString() << endl;
         return(query.lastError().text().size() < 2);
     }
     else
     {
         cout << "INVALID"<<endl;
         valid = open();
         if(valid)
         {
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

bool FileData::Add(computer mycomp)
{
    cout << 104;
     if(valid)
     {
         string info[5];
         for(int i = 0; i < 5; i++)
         {
             info[i] = mycomp.field(i+1);
             sanitize(&info[i]);
         }
         cout << 111;
         QSqlQuery query(connection);
         query.prepare("INSERT INTO Computers(Name,Year,Type,Built,Location)"
                       "VALUES (?,?,?,?,?)");
         for(int i = 0; i < 5; i++)
         {
             cout <<" ? = " << info[i] << endl;
            query.bindValue(i,QString::fromStdString(info[i]));
         }
         query.exec();
         cout << query.lastError().text().toStdString() << endl;
         return(query.lastError().text().size() < 2);
     }
     else
     {
         cout << "INVALID"<<endl;
         valid = open();
         if(valid)
         {
             Add(mycomp);
             return true;
         }
         return false;
     }
}

/************************************************
 * Search<stuff>
 * Takes in a serch term, returns this very cute matrix of strings
 * The Datalayer can handle it from there if it wants to cut something differently
 * ***********************************************/
vector< vector<string> > FileData::SearchComputers(string myString)
{
    int numberOfColumns = 6;
    vector< vector<string> > result;

    QSqlQuery query(connection);
    query.prepare("SELECT * FROM Computers WHERE Name LIKE  ? OR Year LIKE  ? "
                  "OR Type LIKE  ? OR Built LIKE  ? OR Location LIKE  ?");

    myString = '%' + myString + '%';
    for(int i = 0; i < numberOfColumns-1; i++)
    {
        query.bindValue(i, QString::fromStdString(myString));
    }

    query.exec();
    //We have our results, push them into the matrix and off we go
    while(query.next())
    {
        vector<string> row;
        for(int i = 0; i < numberOfColumns; i++)
        {
            row.push_back(query.value(i).toString().toStdString());
        }
        result.push_back(row);
    }
    return result;
}

/************************************************
 * Search function for the scientists
 * ***********************************************/
vector< vector<string> > FileData::SearchScientists(string myString)
{
    int numberOfColumns = 9;
    vector< vector<string> > result;
    QSqlQuery query(connection);
    query.prepare("SELECT * FROM Scientists WHERE FirstName LIKE (?) OR MiddleName LIKE  (?) "
                  "OR LastName LIKE (?) OR Gender LIKE  (?) OR YearOfBirth LIKE  (?) "
                  "OR YearOfDeath LIKE  (?) OR Nationality LIKE  (?) OR Field LIKE (?)");

    myString = '%' + myString + '%';
    for(int i = 0; i < numberOfColumns-1; i++)
    {
        query.bindValue(i,QString::fromStdString(myString));
    }

    query.exec();
    cout << query.lastError().text().toStdString()<< endl;
    //We have our results, push them into the matrix and off we go
    while(query.next())
    {
    vector<string> row;
        for(int i = 0; i < numberOfColumns; i++)
        {
            row.push_back(query.value(i).toString().toStdString());
        }
        result.push_back(row);
    }
    return result;
}


/************************************************
 * Remove<stuff>
 * Erases from the DataBase
 * Risk of Ambiguity, we'll need to fix this.
 * ***********************************************/

void FileData::RemoveComputers(string myString)
{
    QSqlQuery query(connection);
    query.prepare("DELETE FROM Computers WHERE Name= ?;");

    for(int i = 0; i < 1; i++)
    {
        query.bindValue(i, QString::fromStdString(myString));
    }
    query.exec();
}


/************************************************
 * Remove function for the scientists
 * ***********************************************/
void FileData::RemoveScientists(string myString, string myLastString)
{
    QSqlQuery query(connection);
    query.prepare("DELETE FROM Scientists WHERE FirstName = ? AND LastName = ?;");

    string myStrings[2] = {myString, myLastString};

    for(int i = 0; i < 2; i++)
    {
        query.bindValue(i,QString::fromStdString(myStrings[i]));
    }
    query.exec();
    cout << query.lastError().text().toStdString();
}

/*******************************************************
 * JoinTables
 * Takes in either a Scientist or computer
 * Returns a string matrix with data on both
 * Scientist are on column 2 - 10
 * computers are on column 11 - 16
 * *****************************************************/

vector< vector<string> > FileData::JoinTables(ComputerScientist compsci)
{

    vector< vector<string> > ret;
    QSqlQuery query(connection);
    query.prepare("Select * from Scientists where FirstName LIKE ? AND LastName LIKE ?");
    for(int i = 0; i < 2; i++)
    {
       query.bindValue(i,"%" + QString::fromStdString(compsci.field(1 + 2*i)) + "%");
    }
    query.exec();

    cout << query.lastError().text().toStdString() << endl;
    if(!query.next())
    {
        return ret;
    }
    QString sciid;
    sciid = query.value(0).toString();

    query = QSqlQuery(connection);

    query.prepare("SELECT * FROM Owners INNER JOIN Scientists ON Owners.ScientistID = Scientists.ID "
                  "INNER JOIN Computers ON Owners.ComputerID = Computers.ID AND Scientists.ID = ?");
    query.bindValue(0,sciid);
    query.exec();
    int numberOfColumns = 17;
    while(query.next())
    {
    vector<string> row;
        for(int i = 0; i < numberOfColumns; i++)
        {
            row.push_back(query.value(i).toString().toStdString());
        }
        ret.push_back(row);
    }
    return ret;
}

/****************************
 * JoinTables for computers
 * **************************/

vector< vector<string> > FileData::JoinTables(computer comp)
{

    vector< vector<string> > ret;
    QString compid = getId(comp);
    QSqlQuery query(connection);
    query.prepare("SELECT * FROM Owners INNER JOIN Scientists ON Owners.ScientistID = Scientists.ID "
                  "INNER JOIN Computers ON Owners.ComputerID = Computers.ID AND Computers.ID = ?");
    query.bindValue(0,compid);
    query.exec();
    int numberOfColumns = 17;
    while(query.next())
    {
    vector<string> row;
        for(int i = 0; i < numberOfColumns; i++)
        {
            row.push_back(query.value(i).toString().toStdString());
        }
        ret.push_back(row);
    }
    return ret;
}


//****************************************************************
//Load()
//Reads all entries from the database
//Returns true if opening the database worked
//Writes out to Stdout how many entries were loaded for debugging purposes
//****************************************************************
bool FileData::Load(string filename)
{
    if(!valid) cout << "ERROR!";
    QSqlQuery query(connection);
    query.prepare("SELECT"
                  "(SELECT COUNT(DISTINCT ID) FROM Scientists),"
                 "(SELECT COUNT(DISTINCT ID) FROM Computers),"
                  "(SELECT COUNT(DISTINCT ScientistID) FROM Owners)");
     //Done. Report success
    query.exec();
    query.first();
    if(query.lastError().text().size() > 2)
    {
        cout << query.lastError().text().toStdString() << endl;
        return false;
    }
    else
    {
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
vector<string> FileData::explode(const string s, char delim)
{
     vector<string> ret;
     stringstream stream(s);
     string temp;
     while(getline(stream, temp, delim))
     {
          ret.push_back(temp);
     }
     return ret;
}


//****************************************************************
//Returns everything in the database
//Mode = 0: returns all computerscientists
//Mode = 1: Returns all computers
//****************************************************************
vector<vector<string> > FileData::DataSet(int mode = 0)
{
    vector<vector<string> > result;
    int numberOfColumns = 0;
    //Test if there is a valid connection
    if(!valid)
    {
        if(open())
        {
            return DataSet(mode);
        }
        else
        {
            return result;
        }
    }
    QSqlQuery query(connection);
    switch(mode)
    {
        case 0:
        {
            numberOfColumns = 10;
            query.prepare("Select * from Scientists");
            query.exec();
            break;
        }
        case 1:
        {
            numberOfColumns = 7;
            query.prepare("Select * from Computers");
            query.exec();
            break;
        }
    }
    while(query.next())
    {
        vector<string> row;
        for(int i = 0; i < numberOfColumns; i++)
        {
            row.push_back(query.value(i).toString().toStdString());
        }
        result.push_back(row);
    }
    return result;
}


/************************************************************************
 * AddConnection(Scientist,Computer)
 * Adds connection between the two specified entries
 * **********************************************************************/

void FileData::addConnection(ComputerScientist compsci, computer comp)
{

    QString sciid = getId(compsci);
    QSqlQuery query = QSqlQuery(connection);

    query.prepare("Select * from Computers where Name LIKE ? AND Year LIKE ? AND Type LIKE ?");
    for(int i = 0; i < 3; i++)
    {
       query.bindValue(i,QString::fromStdString(comp.field(i+1)));
    }
    query.exec();
    cout << query.lastError().text().toStdString() << endl;
    if(!query.next())
    {
        return;
    }
    QString compid;
    compid = query.value(0).toString();

    query = QSqlQuery(connection);
    query.prepare("Insert into Owners(ScientistID,ComputerID) values (?,?);");
    query.bindValue(0,sciid);
    query.bindValue(1,compid);
    query.exec();

    cout << query.lastError().text().toStdString() << endl;
}

/***************************************
 * update<thing>
 * takes in a computer or scientist and a modified field
 * changes the database to reflect this new value.
 * ************************************/

void FileData::update(ComputerScientist compsci, int field, string newValue)
{
    QString sciid;
    sciid = getId(compsci);
    QSqlQuery query(connection);
    cout << "ID : " << sciid.toStdString()<<endl;
    if(sciid == "-1") return;
    QString column[9] = {"FirstName","MiddleName","LastName","Gender","YearOfBirth","YearOfDeath","Nationality","Fields","Favorite"};

    query.prepare("UPDATE Scientists SET " + column[field-1] + " = ? WHERE ID = ?");

    query.bindValue(0,QString::fromStdString(newValue));
    query.bindValue(1,sciid);
    query.exec();
    cout << query.lastError().text().toStdString();
}

void FileData::update(computer comp, int field, string newValue)
{
    QString compid;
    compid = getId(comp);
    QSqlQuery query(connection);
    cout << "ID : " << compid.toStdString()<<endl;
    if(compid == "-1") return;
    QString column[6] = {"Name","Year","Type","Built","Location","Favorite"};

    query.prepare("UPDATE Computers SET " + column[field-1] + " = ? WHERE ID = ?");

    query.bindValue(0,QString::fromStdString(newValue));
    query.bindValue(1,compid);
    query.exec();
    cout << query.lastError().text().toStdString();
}

QString FileData::getId(ComputerScientist compsci)
{
    QSqlQuery query(connection);
    query.prepare("Select ID from Scientists WHERE FirstName LIKE ? AND LastName LIKE ?");
    for(int i = 0; i < 2; i++)
    {
       query.bindValue(i,"%" + QString::fromStdString(compsci.field(1 + 2*i)) + "%");
       cout << "."<< compsci.field(1 + 2*i) << "." << endl;
    }
    cout << "end"<<endl;
    query.exec();

    cout << query.lastError().text().toStdString() << endl;
    if(!query.next())
    {
        return "-1";
    }
    QString sciid;
    sciid = query.value(0).toString();
    return sciid;
}


QString FileData::getId(computer comp)
{
    QSqlQuery query(connection);
    query.prepare("Select ID from Computers where Name LIKE ? AND Year LIKE ? AND Type LIKE ?");
    for(int i = 0; i < 3; i++)
    {
       query.bindValue(i,QString::fromStdString(comp.field(i+1)));
              cout << "."<< comp.field(1 + 2*i) << "." << endl;
    }
    query.exec();

    cout << query.lastError().text().toStdString() << endl;
    if(!query.next())
    {
        return "-1";
    }
    QString compid;
    compid = query.value(0).toString();
    return compid;
}

/***********************************************
 * favorite<>()
 * Returns all the things marked favorite
 * **********************************************/
vector< vector<string> > FileData::favorite(int mode)
{
    vector<vector<string> > result;
    int numberOfColumns = 0;
    //Test if there is a valid connection
    if(!valid)
    {
        if(open())
        {
            return DataSet(mode);
        }
        else
        {
            return result;
        }
    }
    QSqlQuery query(connection);
    switch(mode)
    {
        case 0:
        {
            numberOfColumns = 10;
            query.prepare("Select * from Scientists WHERE Favorite = 'true'");
            query.exec();
            break;
        }
        case 1:
        {
            numberOfColumns = 7;
            query.prepare("Select * from Computers WHERE Favorite = 'true'");
            query.exec();
            break;
        }
    }
    while(query.next())
    {
        vector<string> row;
        for(int i = 0; i < numberOfColumns; i++)
        {
            row.push_back(query.value(i).toString().toStdString());
        }
        result.push_back(row);
    }
    return result;
}


int FileData::howManySci()
{
    QSqlQuery query(connection);
    query.prepare("SELECT COUNT(*) FROM Scientists");
    query.exec();
    query.first();

    int myInt;
    myInt = query.value(0).toInt();

    return myInt;
}

int FileData::howManyFavSci()
{
    QSqlQuery query(connection);
    query.prepare("Select COUNT(*) FROM Scientists WHERE Favorite = 'true'");
    query.exec();
    query.first();

    int myInt;
    myInt = query.value(0).toInt();

    return myInt;
}

int FileData::howManyComp()
{
    QSqlQuery query(connection);
    query.prepare("SELECT COUNT(*) FROM Computers");
    query.exec();
    query.first();

    int myInt;
    myInt = query.value(0).toInt();

    return myInt;
}

int FileData::howManyFavComp()
{
    QSqlQuery query(connection);
    query.prepare("Select COUNT(*) FROM Computers WHERE Favorite = 'true'");
    query.exec();
    query.first();

    int myInt;
    myInt = query.value(0).toInt();

    return myInt;
}
