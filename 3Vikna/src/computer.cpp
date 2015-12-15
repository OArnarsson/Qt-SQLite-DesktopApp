#include <iostream>
#include <string>
#include "../include/computer.h"

using namespace std;

//****************************************************************
//Constructor
//****************************************************************
computer::computer(string Name, string Year, string Type, string Built, string Location)
{
    name = Name;
    year = Year;
    type = Type;
    built = Built;
    nationality = Location;
    favorite = false;
}

//****************************************************************
//Returns one of the private members of the class
//****************************************************************
string computer::field(int whatField) const
{
    switch(whatField)
    {
        case 1: return name;
        case 2: return year;
        case 3: return type;
        case 4: return built;
        case 5: return nationality;
            default: return "ERROR";
    }
}

//****************************************************************
//Returns how the class is sorted
//****************************************************************
string computer::OrderedName() const
{
    string ret = "";
    for(int i = 1; i < 6; i++)
    {
        ret += field(i) + " ";
    }
    return ret;
}

//****************************************************************
//Dump it to the standard stream
//****************************************************************
ostream& operator <<(ostream& outs, const computer mycomp)
{
    outs << "Computer name: " << mycomp.name << endl;
    outs << "Type: " << mycomp.type << endl;
    outs << "Created in: " << mycomp.year << endl;
    outs << "Was built: " << mycomp.built << endl;
    outs << "Nationality: " << mycomp.nationality << endl;
    return outs;
}

/********************************
 * SetFavorite()
 * Sets if this is a favorite computer
 * ******************************/
void computer::setFavorite(bool newvalue)
{
    favorite = newvalue;
}

/*******************************
 * GetFavorite()
 * Gets if this is a favorite
 * ******************************/
bool computer::getFavorite()
{
    return favorite;
}

/**********************************
 * setField()
 * Changes a specific property of the class
 * ************************************/

void computer::setField(int whatField,string whatValue)
{
    switch(whatField)
    {
        case 1: name = whatValue; break;
        case 2: year = whatValue; break;
        case 3: type = whatValue; break;
        case 4: built = whatValue; break;
        case 5: nationality = whatValue; break;
            default: return;
    }
}
