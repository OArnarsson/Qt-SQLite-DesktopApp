#include "../include/ComputerScientist.h"
#include <set>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;
const int DEFAULT_YEAR = -2015;
string ItoS(int a){
    stringstream Proxy;
    Proxy << a;
    string Prox;
    Proxy >> Prox;
    return Prox;
}

ComputerScientist::ComputerScientist()
{
    firstName = "";
    middleName = "";
    lastName = "";
    gender = "None";
    bornYear = 0;
    diedYear = 0;
}
ComputerScientist::ComputerScientist(string first, string middle, string last, string gen, int born, int died,string nation,string field)
{
    firstName = first;
    middleName = middle;
    lastName = last;
    gender = gen;
    nationality = nation;
    fields = field;
    bornYear = born;
    diedYear = died;
}

ComputerScientist::ComputerScientist(string first, string middle, string last, string gen, int born, int died)
{
    firstName = first;
    middleName = middle;
    lastName = last;
    gender = gen;
    bornYear = born;
    diedYear = died;
}

ComputerScientist::ComputerScientist(string first, string middle, string last, string gen, int born)
{
    firstName = first;
    middleName = middle;
    lastName = last;
    gender = gen;
    bornYear = born;
    diedYear = 0;
}


ComputerScientist::ComputerScientist(string first, string last, string gen, int born, int died)
{
    firstName = first;
    middleName = "";
    lastName = last;
    gender = gen;
    bornYear = born;
    diedYear = died;
}

ComputerScientist::ComputerScientist(string first, string last, string gen, int born)
{
    firstName = first;
    middleName = "";
    lastName = last;
    gender = gen;
    bornYear = born;
    diedYear = 0;
}

string ComputerScientist::getFirst()
{
    return firstName;
}

string ComputerScientist::getMiddle()
{
    return middleName;
}

string ComputerScientist::getLast()
{
    return lastName;
}

string ComputerScientist::ToString(bool LastNameFirst = false) const{
    stringstream ret;
    string First,Mid,Last;
    if(LastNameFirst){
        First = lastName;
        Mid = firstName;
        Last = middleName;
    }
    else{
        First = firstName;
        Mid = middleName;
        Last = lastName;
    }
    ret << ((First != "") ? (First + " "):"");
    ret << ((Mid != "") ? (Mid + ""):"");
    ret << ((Last != "") ? (Last + ","):",");
    ret << gender << ",";
    ret << ((bornYear != DEFAULT_YEAR) ? ItoS(bornYear):"") << ",";
    ret << ((diedYear != DEFAULT_YEAR) ? ItoS(diedYear):"");
    return ret.str();
}
string ComputerScientist::OrderedName() const {
    return firstName + " "+ middleName +  " " + lastName;
}
ostream& operator <<(ostream& outs, const ComputerScientist myScientist)
{
    outs << "First name: " << myScientist.firstName << endl;
    if(myScientist.middleName.length() > 1)
    {
      outs << "Middle name: " << myScientist.middleName << endl;
    }

    outs << "Last name: " << myScientist.lastName << endl;
    outs << "Gender: " << myScientist.gender << endl;
    outs << "Born: " << myScientist.bornYear << endl;

    if(myScientist.diedYear > 1)
    {
        outs << "First name: " << myScientist.firstName << endl;
    }
    return outs;
}

vector <ComputerScientist> Find(string mySearch, vector<ComputerScientist> myVector)
{
    vector <ComputerScientist> foundDudes;

    for (unsigned int i = 0; i < myVector.size(); i++)
    {
       if(myVector[i].OrderedName().find(mySearch) != -1)
       {
          foundDudes.push_back(myVector[i]);
       }
    }

    return foundDudes;
}

vector <ComputerScientist> ComputerScientist::SortFirst(vector <ComputerScientist> theList)
{

    int lowestFirst;

    for (unsigned int j = 0; j < theList.size(); j++)
    {
        lowestFirst = j;
        for (int i = j+1; i < theList.size(); i++)
            {
                if (theList[i].firstName < theList[lowestFirst].firstName)
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

vector <ComputerScientist> ComputerScientist::SortMiddle(vector <ComputerScientist> theList)
{

    int lowestFirst;

    for (unsigned int j = 0; j < theList.size(); j++)
    {
        lowestFirst = j;
        for (int i = j+1; i < theList.size(); i++)
            {
                if (theList[i].middleName < theList[lowestFirst].middleName)
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

vector <ComputerScientist> ComputerScientist::SortLast(vector <ComputerScientist> theList)
{

    int lowestFirst;

    for (unsigned int j = 0; j < theList.size(); j++)
    {
        lowestFirst = j;
        for (int i = j+1; i < theList.size(); i++)
            {
                if (theList[i].lastName < theList[lowestFirst].lastName)
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

vector <ComputerScientist> ComputerScientist::SortGender(vector <ComputerScientist> theList)
{

    int lowestFirst;

    for (unsigned int j = 0; j < theList.size(); j++)
    {
        lowestFirst = j;
        for (int i = j+1; i < theList.size(); i++)
            {
                if (theList[i].gender < theList[lowestFirst].gender)
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

vector <ComputerScientist> ComputerScientist::SortBorn(vector <ComputerScientist> theList)
{

    int lowestFirst;

    for (unsigned int j = 0; j < theList.size(); j++)
    {
        lowestFirst = j;
        for (int i = j+1; i < theList.size(); i++)
            {
                if (theList[i].bornYear < theList[lowestFirst].bornYear)
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

vector <ComputerScientist> ComputerScientist::SortDied(vector <ComputerScientist> theList)
{

    int lowestFirst;

    for (unsigned int j = 0; j < theList.size(); j++)
    {
        lowestFirst = j;
        for (int i = j+1; i < theList.size(); i++)
            {
                if (theList[i].diedYear < theList[lowestFirst].diedYear)
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
