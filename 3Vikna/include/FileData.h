#ifndef FILEDATA_H_INCLUDED
#define FILEDATA_H_INCLUDED
#include <set>
#include "ComputerScientist.h"
class FileData{
     private:
     string base;
     set<ComputerScientist> compsci;
     public:
     FileData(string DataBaseFile);
     void Add(ComputerScientist scientist);
     bool Save();
};


#endif // FILEDATA_H_INCLUDED
