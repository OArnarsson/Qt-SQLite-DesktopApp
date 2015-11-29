#ifndef COMPUTERSCIENTIST_H
#define COMPUTERSCIENTIST_H
#include <string>
#include <set>
#include <vector>
#include <fstream>

using namespace std;

class ComputerScientist
{
    public:
        string ToString(bool LastNameFirst) const;
        string OrderedName() const;
        ComputerScientist();
        ComputerScientist(string first, string middle, string last, string gen, int born, int died);
        ComputerScientist(string first, string middle, string last, string gen, int born);
        ComputerScientist(string first, string last, string gen, int born, int died);
        ComputerScientist(string first, string last, string gen, int born);
        friend ostream& operator <<(ostream& outs, const ComputerScientist myScientist);
        string getFirst();
        string getMiddle();
        string getLast();
        bool operator<(ComputerScientist other) const
            {
                return firstName + " "+ middleName +  " " + lastName < other.OrderedName();
            }
        vector <ComputerScientist> Find(string mySearch, vector <ComputerScientist> myVector);


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
