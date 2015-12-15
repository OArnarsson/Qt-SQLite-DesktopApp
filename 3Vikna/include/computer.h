#ifndef COMPUTER
#define COMPUTER

#include <string>
#include <iostream>

using namespace std;

class computer
{
    private:
    string name;
    string year;
    string type;
    string built;
    string nationality;
    bool favorite;

    public:
    computer(string Name = "", string Year = "", string Type = "", string Built = "true", string Location = "");
    string field(int whatField) const;
    void setField(int whatField,string whatValue);
    string OrderedName() const;
    void setFavorite(bool newvalue);
    bool getFavorite();
    bool operator < (computer other) const
    {
            return OrderedName() < other.OrderedName();
    }
    friend ostream& operator <<(ostream& outs, const computer mycomp);
};

#endif // COMPUTER
