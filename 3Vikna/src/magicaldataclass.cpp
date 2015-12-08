#include <iostream>
#include <vector>
#include <string>
#include "../include/ComputerScientist.h"
#include "../include/FileData.h"
#include "../include/magicaldataclass.h"


//Default Constructor
MagicalDataClass::MagicalDataClass(){
    sortingOption = 1;
}

//Constructor
MagicalDataClass::MagicalDataClass(string filename){
    Database = new FileData(filename);
    sortingOption = 1;
}

/*******************************************
 * SetSort()
 * Used to tell the datalayer how the results should be sorted
 * ****************************************/
void MagicalDataClass::SetSort(int option){
    if(option < 1){
        option = 1;
    }
    sortingOption = option % 7;
}

/*******************************************
 * Add()
 * Takes a stringvector, sees if it fits to any datatype,
 * and passes it down to FileData for SQL storage
 * ****************************************/
void MagicalDataClass::Add(vector<string> entry){
    for(int i = 0; i < entry.size(); i++){
        entry[i] += " ";
    }
    if(entry.size() == 8){
         ComputerScientist newEntry(entry[0],entry[1],entry[2],entry[3],entry[4],entry[5],entry[6],entry[7]);
             (*Database).Add(newEntry);
    }
    else if(entry.size() == 5){
        computer newEntry(entry[0],entry[1],entry[2],entry[3]);
            (*Database).Add(newEntry);
    }
}


/*******************************************
 * Sort()
 * Remnant from project one.
 * Do we want to do something with this in week 2?
 * ****************************************/
vector <ComputerScientist> MagicalDataClass::Sort(vector <ComputerScientist> theList, const int whatField){
    int lowestFirst;

    for (unsigned int j = 0; j < theList.size(); j++)
    {
        lowestFirst = j;
        for (unsigned int i = j+1; i < theList.size(); i++)
            {
                if (theList[i].field(whatField) < theList[lowestFirst].field(whatField))
                {
                    lowestFirst = i;
                }
            }

        if(lowestFirst != j)
        {
            swap(theList[j], theList[lowestFirst]);
        }
    }
        return theList;
}

/**********************************************************************************
 * GetAll()
 * Takes inn an (empty) vector of either scientists or computers and populates it
 * Fills in the entire database worth of scientists or comuters
 * *******************************************************************************/
void MagicalDataClass::GetAll(vector<ComputerScientist>& vec){
    vector< vector<string> > MyQuery;
    MyQuery = (*Database).DataSet(0);
    vec = stringtoscientist(MyQuery);
}
/***************/
void MagicalDataClass::GetAll(vector<computer>& vect){
    cout << 91<<endl;
    vector< vector<string> > MyQuery;
    MyQuery = (*Database).DataSet(1);
    vect = stringtocomputer(MyQuery);
}

/********************************************************************************
 * Search()
 * Takes in a substring
 * populates a vector with all the computers/scientists that fit the term
 * ******************************************************************************/
void MagicalDataClass::Search(vector<computer>& vect, string substring){
    vector< vector<string> > MyQuery;
    MyQuery = (*Database).SearchComputers(substring);

    for(unsigned int i = 0; i < MyQuery.size(); i++){
        string info[8];
        for(unsigned int j = 0; j < MyQuery[i].size();j++){
            info[j] = MyQuery[i][j];
        }
        computer compsci(info[1],info[2],info[3],info[4],info[5]);
        vect.push_back(compsci);
    }
    vect = stringtocomputer(MyQuery);
}

//******************

void MagicalDataClass::Search(vector<ComputerScientist>& vect, string substring){
    vector< vector<string> > MyQuery;
    MyQuery = (*Database).SearchScientists(substring);
    for(unsigned int i = 0; i < MyQuery.size(); i++){
        string info[9];
        for(unsigned int j = 0; j < MyQuery[i].size();j++){
            info[j] = MyQuery[i][j];
        }
        ComputerScientist compsci(info[1],info[2],info[3],info[4],info[5],info[6],info[7],info[8]);
        vect.push_back(compsci);
    }
    vect = stringtoscientist(MyQuery);
}
//****************************************************************************
//StringToScientist(vector< vector<string> >)
//Takes a string matrix and jams it into a vector of computerscientist
//****************************************************************************

vector<ComputerScientist> MagicalDataClass::stringtoscientist(vector<vector<string> > MyQuery){
    vector<ComputerScientist> vec;
    for(unsigned int i = 0; i < MyQuery.size(); i++){
        string info[9];
        for(unsigned int j = 0; j < MyQuery[i].size();j++){
            info[j] = MyQuery[i][j];
        }
        ComputerScientist compsci(info[1],info[2],info[3],info[4],info[5],info[6],info[7],info[8]);
        vec.push_back(compsci);
    }
    return vec;
}

//****************************************************************************
//StringTocomputer(vector< vector<string> >)
//Takes a string matrix and jams it into a vector of computers
//****************************************************************************

vector<computer> MagicalDataClass::stringtocomputer(vector< vector<string> > vec){
    vector<computer> ret;
    for(unsigned int i = 0; i < vec.size(); i++){
        string info[6];
        for(unsigned int j = 0; j < vec[i].size();j++){
            info[j] = vec[i][j];
        }
        computer compsci(info[1],info[2],info[3],info[4],info[5]);
        ret.push_back(compsci);
    }
    return ret;
}
