#include <iostream>
#include <vector>
#include <string>
#include "../include/ComputerScientist.h"
#include "../include/FileData.h"
#include "../include/magicaldataclass.h"

string ToLower(string s){
    for(unsigned int i = 0; i < s.length(); i++){
        s[i] = tolower(s[i]);
    }
   return s;
}

MagicalDataClass::MagicalDataClass(){
    sortingOption = 1;
}

MagicalDataClass::MagicalDataClass(string filename){
    Database = new FileData(filename);
    sortingOption = 1;
}

void MagicalDataClass::SetSort(int option){
    if(option < 1){
        option = 1;
    }
    sortingOption = option % 7;
}

void MagicalDataClass::Add(vector<string> entry){
    for(int i = 0; i < 8; i++){
        entry[i] += " ";
    }
    ComputerScientist newEntry(entry[0],entry[1],entry[2],entry[3],entry[4],entry[5],entry[6],entry[7]);
    (*Database).Add(newEntry);
}

vector <ComputerScientist> MagicalDataClass::Find(string mySearch, vector<ComputerScientist> myVector)
{
    vector <ComputerScientist> foundDudes;

    for (unsigned int i = 0; i < myVector.size(); i++)
    {
       string seek = ToLower((myVector[i]).OrderedName());
       if(seek.find(ToLower(mySearch)) != -1)
       {
          foundDudes.push_back(myVector[i]);
       }
    }

    return foundDudes;
}


vector <ComputerScientist> MagicalDataClass::Sort(vector <ComputerScientist> theList, const int whatField)
{
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

void MagicalDataClass::GetAll(vector<ComputerScientist>& vec){
    vec = (*Database).DataSet(0);
}
void MagicalDataClass::Search(vector<ComputerScientist>&, string substring){
    vector<ComputerScientist> Ret = (*Database).DataSet(0);
    Ret = Find(substring,Ret);
    Ret = Sort(Ret,sortingOption);
}

