#ifndef COMPUTERSCIENTIST_H
#define COMPUTERSCIENTIST_H
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class ComputerScientist
{
    public:
        string ToString(bool LastNameFirst) const;
        string OrderedName() const;
        ComputerScientist();
        ComputerScientist(string first, string middle, string last, string gen, string born, string died,string nation,string field);
        ComputerScientist(string first, string middle, string last, string gen, string born, string died);
        ComputerScientist(string first, string last, string gen, string born, string died);
        ComputerScientist(string first, string last, string gen, string born);
        friend ostream& operator <<(ostream& outs, const ComputerScientist myScientist);
        string getFirst();
        string getMiddle();
        string getLast();
        bool operator<(ComputerScientist other) const
            {
                return firstName + " "+ middleName +  " " + lastName < other.OrderedName();
            }
        string field(const int whatField);
        void setFavorite(bool newvalue);
        bool getFavorite();

    protected:
    private:
        string firstName;
        string middleName;
        string lastName;
        string gender;
        string nationality;
        string fields;
        string bornYear;
        string diedYear;
        bool favorite;

};

#endif // COMPUTERSCIENTIST_H
