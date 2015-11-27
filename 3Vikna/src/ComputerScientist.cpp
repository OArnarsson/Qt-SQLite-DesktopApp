#include "../include/ComputerScientist.h"
#include <string>
#include <sstream>
using namespace std;

ComputerScientist::ComputerScientist()
{
    firstName = "";
    middleName = "";
    lastName = "";
    gender = "None";
    bornYear = 0;
    diedYear = 0;
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

string ComputerScientist::ToString() const{
    stringstream ret;
    ret << firstName << ",";
    ret << middleName << ",";
    ret << lastName << ",";
    ret << gender << ",";
    ret << bornYear << ",";
    ret << diedYear << "\n";
    return ret.str();
}
string  const ComputerScientist::LastName() {
    return lastName;
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

