#ifndef MAGICALDATACLASS_H
#define MAGICALDATACLASS_H

#include <iostream>
#include <vector>
#include <string>
#include "../include/ComputerScientist.h"
#include "../include/FileData.h"
#include "../include/computer.h"

using namespace std;

class MagicalDataClass
{
    private:
    FileData* Database;
    int sortingOption;
    int compSortingOption;
    vector <ComputerScientist> Sort(vector <ComputerScientist> theList, const int whatField);
    vector <computer> Sort(vector <computer> theList, const int whatField);
    public:
    MagicalDataClass();
    MagicalDataClass(string filename);
    void GetAll(vector<ComputerScientist>& vec);
    void GetAll(vector<computer>& vect);
    void Search(vector<ComputerScientist>&vec, string substring);
    void Search(vector<computer>& vec, string substring);
    void thin(vector<computer>& vec, string term);
    void thin(vector<ComputerScientist>& vec, string term);
    void remove(ComputerScientist vec);
    void remove(computer vec);
    void Add(vector<string> entry);
    void SetSort(int option,int mode);
    void AddConnection(ComputerScientist compsci,computer comp);
    void setFavorite(ComputerScientist compsci, bool marker);
    void setFavorite(computer comp, bool marker);
    vector<ComputerScientist> stringtoscientist(vector< vector<string> > vect);
    vector<computer> stringtocomputer(vector< vector<string> > vect);
    vector<computer> getConnections(ComputerScientist compsci);
    vector<ComputerScientist> getConnections(computer comp);

};

#endif // MAGICALDATACLASS_H

