#ifndef FILEDATA_H_INCLUDED
#define FILEDATA_H_INCLUDED
#include <set>
#include <vector>
#include "ComputerScientist.h"

//Class FileData
//Responsible for storing all scientists until writing
class FileData{
     private:
          string base;
          set<ComputerScientist> compsci;
     public:
          FileData(string DataBaseFile);
          void Add(ComputerScientist scientist);
          bool Save();
          bool Load();
          vector<string> explode(const string s, char delim);
};


#endif // FILEDATA_H_INCLUDED
