#include <iostream>
#include <vector>

using namespace std;

int main()
{
    string input = "Derp";
    vector <string> myStuff;

    while(input.length() > 1)
    {
        cin >> input;
        myStuff.push_back(input);
    }

    int lowestFirst;

    for (j = 0; j < myStuff.size(); j++)
    {
        lowestFirst = j;
        for ( i = j+1; i < myStuff.size(); i++)
            {
                if (myStuff[i] < myStuff[lowestFirst])
                {
                    iMin = i;
                }
            }

        if(lowestFirst != j)
        {
            swap(myStuff[j], myStuff[lowestFirst]);
        }
    }

    for(unsigned int i = 0; i < myStuff.size(); i++)
    {
        cout << myStuff[i] << endl;
    }

    return 0;
}
