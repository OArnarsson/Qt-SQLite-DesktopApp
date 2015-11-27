#include <iostream>
#include <fstream>
#include <set>
#include "../include/FileData.h"
#include "../include/ComputerScientist.h"


FileData::FileData(string DataBaseFile){
     base = DataBaseFile;
     //TODO
     //Add loading the database
}

void FileData::Add(ComputerScientist scientist){
     compsci.insert(scientist);

}
