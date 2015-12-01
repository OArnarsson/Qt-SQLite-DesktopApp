#ifndef MAGICALDATACLASS_H
#define MAGICALDATACLASS_H

#include <iostream>
#include <vector>
#include <string>
#include "../include/ComputerScientist.h"
#include "../include/FileData.h"

using namespace std;

class MagicalDataClass{
    private:
    FileData* Database;
    int sortingOption;
    vector <ComputerScientist> Find(string mySearch, vector<ComputerScientist> myVector);
    vector <ComputerScientist> Sort(vector <ComputerScientist> theList, const int whatField);
    public:
    MagicalDataClass();
    MagicalDataClass(string filename);
    vector <ComputerScientist> GetAll();
    vector <ComputerScientist> Search(string SubName);
    void Add(vector<string> entry);
    void SetSort(int option);

};

#endif // MAGICALDATACLASS_H

