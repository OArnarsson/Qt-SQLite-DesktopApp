#ifndef COMPUTERSCIENTIST_H
#define COMPUTERSCIENTIST_H
#include <string>
#include <fstream>

using namespace std;

class ComputerScientist
{
    public:
        string ToString(bool LastNameFirst) const;
        string const OrderedName();
        ComputerScientist();
        ComputerScientist(string first, string middle, string last, string gen, int born, int died);
        ComputerScientist(string first, string middle, string last, string gen, int born);
        ComputerScientist(string first, string last, string gen, int born, int died);
        ComputerScientist(string first, string last, string gen, int born);
        friend ostream& operator <<(ostream& outs, const ComputerScientist myScientist);
        bool operator<(ComputerScientist other) const
            {
                return firstName + " "+ middleName +  " " + lastName < other.OrderedName();
            }


    protected:
    private:
        string firstName;
        string middleName;
        string lastName;
        string gender;
        int bornYear;
        int diedYear;

};

#endif // COMPUTERSCIENTIST_H
