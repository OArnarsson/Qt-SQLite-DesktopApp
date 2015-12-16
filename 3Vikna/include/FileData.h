#ifndef FILEDATA_H_INCLUDED
#define FILEDATA_H_INCLUDED
#include <set>
#include <vector>
#include "ComputerScientist.h"
#include "computer.h"
#include <QtSql>

//Class FileData
//Responsible for storing all scientists until writing
class FileData
{
     private:
          string base;
          QSqlDatabase connection;
          bool valid;
          bool open();
     public:
          FileData(string DataBaseFile);
          bool Add(ComputerScientist scientist);
          bool Add(computer scientist);
          bool Load(string filename = "");
          vector< vector<string> > DataSet(int mode);
          vector< vector<string> > favorite(int mode);
          vector<string> explode(const string s, char delim);
          vector< vector<string> > SearchComputers(string myString);
          vector< vector<string> > SearchScientists(string myString);
          void addConnection(ComputerScientist compsci, computer comp);
          void RemoveComputers(string myString);
          void RemoveScientists(string myString, string myLastString);

          vector< vector<string>> Connections(int mode);
          void removeConnection(ComputerScientist compsci,computer comp);
          vector< vector<string > > JoinTables(ComputerScientist compsci);
          vector< vector<string > > JoinTables(computer comp);

          QString getId(computer comp);
          QString getId(ComputerScientist compsci);

          void update(ComputerScientist compsci, int field, string newValue);
          void update(computer comp, int field, string newValue);

          int howManySci();
          int howManyFavSci();
          int howManyComp();
          int howManyFavComp();

};


#endif // FILEDATA_H_INCLUDED
