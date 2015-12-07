#ifndef MAGICALDATACLASS_H
#define MAGICALDATACLASS_H

#include <iostream>
#include <vector>
#include <string>
#include "../include/ComputerScientist.h"
#include "../include/FileData.h"
#include "../include/computer.h"

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
    void GetAll(vector<ComputerScientist>& vec);
    void GetAll(vector<computer>& vect);
    void Search(vector<ComputerScientist>&vec, string substring);
    void Search(vector<computer>& vec, string substring);
    void Add(vector<string> entry);
    void SetSort(int option);
    vector<ComputerScientist> stringtoscientist(vector<vector<string>> vect);
    vector<computer> stringtocomputer(vector<vector<string>> vect);

};

#endif // MAGICALDATACLASS_H

