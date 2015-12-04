#ifndef FILEDATA_H_INCLUDED
#define FILEDATA_H_INCLUDED
#include <set>
#include <vector>
#include "ComputerScientist.h"
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

          bool Load(string filename = "");
          vector<ComputerScientist>DataSet();
          vector<string> explode(const string s, char delim);
};


#endif // FILEDATA_H_INCLUDED
