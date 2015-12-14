#include "../include/ComputerScientist.h"
#include <set>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;
const string DEFAULT_YEAR = "-2015";
string ItoS(int a)
{
    stringstream Proxy;
    Proxy << a;
    string Prox;
    Proxy >> Prox;
    return Prox;
}

//****************************************************************
//Constructor
//****************************************************************
ComputerScientist::ComputerScientist()
{
    firstName = "";
    middleName = "";
    lastName = "";
    gender = "None";
    bornYear = DEFAULT_YEAR;
    diedYear = DEFAULT_YEAR;
    favorite = false;
}

//****************************************************************
//Constructor
//****************************************************************
ComputerScientist::ComputerScientist(string first, string middle, string last, string gen, string born, string died,string nation,string field)
{
    firstName = first;
    middleName = middle;
    lastName = last;
    gender = gen;
    nationality = nation;
    fields = field;
    bornYear = born;
    diedYear = died;
    favorite = false;
}

//****************************************************************
//Constructor
//****************************************************************
ComputerScientist::ComputerScientist(string first, string middle, string last, string gen, string born, string died)
{
    firstName = first;
    middleName = middle;
    lastName = last;
    gender = gen;
    bornYear = born;
    diedYear = died;
    favorite = false;
}

//****************************************************************
//Constructor
//****************************************************************
ComputerScientist::ComputerScientist(string first, string last, string gen, string born, string died)
{
    firstName = first;
    middleName = "";
    lastName = last;
    gender = gen;
    bornYear = born;
    diedYear = died;
    favorite = false;
}

//****************************************************************
//Constructor
//****************************************************************
ComputerScientist::ComputerScientist(string first, string last, string gen, string born)
{
    firstName = first;
    middleName = "";
    lastName = last;
    gender = gen;
    bornYear = born;
    diedYear = "0";
    favorite = false;
}

//****************************************************************
//Returns the first name
//****************************************************************
string ComputerScientist::getFirst()
{
    return firstName;
}

//****************************************************************
//Returns the middle name
//****************************************************************
string ComputerScientist::getMiddle()
{
    return middleName;
}

//****************************************************************
//Returns the last name
//****************************************************************
string ComputerScientist::getLast()
{
    return lastName;
}

//****************************************************************
//Converts the class into a string
//****************************************************************
string ComputerScientist::ToString(bool LastNameFirst = false) const
{
    stringstream ret;
    string First,Mid,Last;
    if(LastNameFirst)
    {
        First = lastName;
        Mid = firstName;
        Last = middleName;
    }
    else
    {
        First = firstName;
        Mid = middleName;
        Last = lastName;
    }
    ret << ((First != "") ? (First + " "):"");
    ret << ((Mid != "") ? (Mid + ""):"");
    ret << ((Last != "") ? (Last + ","):",");
    ret << gender << ",";
    ret << ((bornYear != DEFAULT_YEAR) ? bornYear:"") << ",";
    ret << ((diedYear != DEFAULT_YEAR) ? diedYear:"") << ",";
    ret << nationality << ",";
    ret << fields;
    return ret.str();
}

//****************************************************************
//Converts the class into a string used in the search function
//****************************************************************
string ComputerScientist::OrderedName() const
{
    return firstName + " "+ middleName +  " " + lastName + " " + gender + " " + nationality + " " + bornYear + " " + diedYear + " " + fields;
}

//****************************************************************
//Overloads the "<<" operator for output
//****************************************************************
ostream& operator <<(ostream& outs, const ComputerScientist myScientist)
{
    outs << "First name: " << myScientist.firstName << endl;
    if(myScientist.middleName.length() > 1)
    {
      outs << "Middle name: " << myScientist.middleName << endl;
    }

    outs << "Last name: " << myScientist.lastName << endl;
    outs << "Gender: " << myScientist.gender << endl;
    outs << "Nationality: " << myScientist.nationality << endl;
    if(myScientist.bornYear != DEFAULT_YEAR)
    {
        outs << "Born: " << myScientist.bornYear << endl;
    }

    if(myScientist.diedYear != DEFAULT_YEAR)
    {
        outs << "Died: " << myScientist.diedYear << endl;
    }

    outs << "Fields: " << myScientist.fields << endl;
    return outs;
}

//****************************************************************
//The search function
//****************************************************************
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

//****************************************************************
//Function used for defining the field used in search and sort
//****************************************************************
string ComputerScientist::field(const int whatField)
{
    if(whatField == 1)
    {
        return firstName;
    }
    else if(whatField == 2)
    {
        return middleName;
    }
    else if(whatField == 3)
    {
        return lastName;
    }
    else if(whatField == 4)
    {
       return gender;
    }
    else if(whatField == 5)
    {
        return bornYear;
    }
    else if(whatField == 6)
    {
        return diedYear;
    }
    else if(whatField == 7){
        return nationality;
    }
    else if(whatField == 8){
        return fields;
    }
    else return "Error";
}

void ComputerScientist::setFavorite(bool newvalue)
{
    favorite = newvalue;
}

bool ComputerScientist::getFavorite()
{
    return favorite;
}
