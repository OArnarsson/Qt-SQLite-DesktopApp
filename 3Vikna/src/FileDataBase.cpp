#include <iostream>
#include <fstream>
#include <set>
#include "../include/FileData.h"
#include "../include/ComputerScientist.h"

//Constructor.
//Reads from the database on the file (if exists)
//Note: Unimplemented feature: Load from disk
FileData::FileData(string DataBaseFile){
     base = DataBaseFile;
     //TODO
     //Add loading the database
}

//Add
//Accepts a ComputerScientist class
//Stores it in memory until ready to write to disk
void FileData::Add(ComputerScientist scientist){
     compsci.insert(scientist);
}

//Save
//Writes all stored computer scientists to disk
//Returns true if successful, False otherwise
bool FileData::Save(){
     ofstream Outstream;
     Outstream.open(base);
     if(Outstream.is_open()){
          //Iterates trough the entire set; printing each entry to the file in turn
          for (set<ComputerScientist>::iterator it=compsci.begin(); it!=compsci.end(); ++it){
               Outstream << (*it).ToString();
          }
          Outstream.close();
          return true;
     }
     else{
          return false; //File is not opened; error.
     }
}
