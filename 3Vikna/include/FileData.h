#ifndef FILEDATA_H_INCLUDED
#define FILEDATA_H_INCLUDED
#include <set>
#include <vector>
#include "ComputerScientist.h"
#include "computer.h"
#include <QtSql>

//Class FileData
//Responsible for storing all scientists until writing
class FileData{
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
          vector<string> explode(const string s, char delim);
          vector< vector<string> > SearchComputers(string myString);
          vector< vector<string> > SearchScientists(string myString);
          void RemoveComputers(string myString);
          void RemoveScientists(string myString, string myLastString);
          void JoinTables();
};


#endif // FILEDATA_H_INCLUDED
