#ifndef UI_H
#define UI_H

#include "magic.h"
#include <iostream>
#include "ComputerScientist.h"
#include "magicaldataclass.h"
#include "computer.h"
#include <sstream>

using namespace std;
class UI
{
public:
    UI()
    {
        MyDataLayer = new MagicalDataClass("CompDataBase.sqlite");
    }

    /************************************************
     * start
     * actually runs the program
     * ***********************************************/
    void start()
    {
        while (true)
        {
            cout << "Which database would you like to access?" << endl;
            cout << "----- 1 Computer scientists." << endl;
            cout << "----- 2 Computers." << endl;
            cout << "----- 3 for ~Magic~." << endl;
            cout << "----- q to quit" << endl;
            char operation = getChar();
            
            if (operation == '1')compSci(); else
                if (operation == '2') _computer(); else
                    if (operation == 'q' || operation == 'Q') break;
                      if(operation == '3') magic();
                          else cout << "Please choose a valid option." << endl;
        }
    }
    
private:
    MagicalDataClass* MyDataLayer;
    
    
    /************************************************
     * getChar()
     * get's a single character from Stdin
     * ***********************************************/
    char getChar()
    {
        char c;
        cin >> c;
        return c;
    }
    
    
    /************************************************
     * compSci()
     * The computer scientist database menu
     * ***********************************************/
    void compSci()
    {
        while (true)
        {
            cout << "This is a Computer Scientist database." << endl;
            cout << "----- 1 to add an entry." << endl;
            cout << "----- 2 to remove entries." << endl;
            cout << "----- 3 to search entries." << endl;
            cout << "----- 4 to list all entries." << endl;
            cout << "----- 5 for sorting options." << endl;
            cout << "----- 6 for connections." << endl;
            cout << "----- Any other to go back." << endl;

            char operation = getChar();
            
            if (operation == '1') addToCompSci();
            if (operation == '2') removeCompSci();
            if (operation == '3') searchCompSci();
            if (operation == '4') printCompSci();
            if (operation == '5') sortCompSci();
            if (operation == '6') connectCompSci();
            else break;
        }
        
    }
    
    /************************************************
     * addToCompSci
     * Adds a name to the computer scientist databse
     * ***********************************************/
    void addToCompSci()
    {
        while (true)
        {
            string info[8] = {"First name","Middle name(s)","Last Name","Gender","Birth Year","Death Year","Nationality","Fields of profession"};
            vector<string> entering;
            
            for(int i = 0; i < 8; i++)
            {
                cout << "Please enter the " << info[i] << " of the scientist you're adding.\n Leave blank if no information is to be entered\n";
                char entry[64];
                cin.ignore(256,'\n');
                cin.get(entry,64);
                entering.push_back(string(entry));
                cin.clear();
            }
            for(int i = 0; i < 8; i++)
            {
                for(unsigned int n = 0; n < entering[i].size(); n++)
                {
                    if(entering[i][n] == ',')
                    {
                        entering[i][n] = ' ';
                    }
                }
            }
            (*MyDataLayer).Add(entering);
            cout << "//Computer scientist added." << endl;
            cout << "----- 1 to add another computer scientist." << endl;
            cout << "----- Any other to go back." << endl;
            char operation = getChar();
            if (operation == '1') addToCompSci();
            else break;
        }
    }
    
    /*********************************************************************
     * RemoveCompsci()
     * Asks for a name to remove
     * removes it
     ********************************************************************/
    void removeCompSci()
    {
        string name;
        vector<ComputerScientist> compsci;
        cout << "Please enter the name or characteristic of the scientist to remove" << endl;
        cin >> name;
        (*MyDataLayer).Search(compsci,name);
        while(compsci.size() > 1)
        {
            printCompSci(compsci);
            cout << "There is ambiguity in your choice, please type in a distinct idenifier" << endl;
            cin >> name;
            (*MyDataLayer).thin(compsci,name);
        }
        cout << compsci[0];
        cout << "Are you sure you wish to delete the above entry? (y/n)" << endl;
        char ent;
        ent = getchar();
        if(ent == 'y' || ent == 'Y')
        {
            (*MyDataLayer).remove(compsci[0]);
        }
    }
    
    /************************************************
     * SearchCompSci
     * Asks the database for a vector of all scientist matching a term
     * Prints it to StdOut
     * ***********************************************/
    
    void searchCompSci()
    {
        cout << "Please enter the name you wish to search for." << endl;
        string term;
        cin.ignore();
        getline(cin, term);
        vector <string> newSearchTerm = explode(term, ' ');
        vector<ComputerScientist> vec;
        (*MyDataLayer).Search(vec,term);

        for(unsigned int i = 0; i < newSearchTerm.size(); i++)
        {
            (*MyDataLayer).thin(vec, newSearchTerm[i]);
        }
        printCompSci(vec);
    }

    vector<string> explode(const string s, char delim)
    {
         vector<string> ret;
         stringstream stream(s);
         string temp;
         while(getline(stream, temp, delim))
         {
              ret.push_back(temp);
         }
         return ret;
    }

    /************************************************
     * PrintCompSci
     * prints a vector
     * ***********************************************/
    void printCompSci(vector<ComputerScientist> list)
    {
        cout << endl;
        cout <<"______________________________"<<endl;
        for(unsigned int i = 0; i < list.size(); i++)
        {
            cout << list[i] << endl;
            cout <<"______________________________"<<endl;
        }
        cout << endl;
        cout << "***********************************" << endl;
        cout << "        "<<list.size()<< " matching entries!"<<endl;
        cout << "***********************************" << endl << endl;
    }
    
    void printCompSci()
    {
        vector<ComputerScientist> vec;
        (*MyDataLayer).GetAll(vec);
        printCompSci(vec);
    }
    
    /************************************************
     * sortCompSci
     * Changes the sorting pattern
     * ***********************************************/
    void sortCompSci()
    {
        while (true)
        {
            cout << "Sort alphabetically or alphanumeracally by:" << endl;
            cout << "First name, last name, gender, year of birth or year of death." << endl;
            cout << "----- 1 First name." << endl;
            cout << "----- 2 Middle name." << endl;
            cout << "----- 3 Last name." << endl;
            cout << "----- 4 Gender." << endl;
            cout << "----- 5 Year of birth." << endl;
            cout << "----- 6 Year of death." << endl;
            cout << "----- Any other to go back." << endl;
            char operation = getChar();
            if (operation == '1') (*MyDataLayer).SetSort(1);
            if (operation == '2') (*MyDataLayer).SetSort(2);
            if (operation == '3') (*MyDataLayer).SetSort(3);
            if (operation == '4') (*MyDataLayer).SetSort(4);
            if (operation == '5') (*MyDataLayer).SetSort(5);
            if (operation == '6') (*MyDataLayer).SetSort(6);
            break;
        }
    }
    
    void connectCompSci()
    {
        while (true)
        {
            cout << "Do you want to search connections or add a new connection?" << endl;
            cout << "----- 1 Search connections" << endl;
            cout << "----- 2 Add a new connection" << endl;
            cout << "----- Any other to go back." << endl;
            char operation = getChar();
            if (operation == '1') searchConnectionCompSci();
            if (operation == '2') addConnection();
            break;
        }
    }

    void searchConnectionCompSci()
    {
        vector<ComputerScientist> vec;
        cout << "Please enter the name or identifying qualifier for the Scientist:"<<endl;
        string term;
        cin.ignore();
        getline(cin, term);
        vector <string> newSearchTerm = explode(term, ' ');
        (*MyDataLayer).Search(vec,term);

        for(unsigned int i = 0; i < newSearchTerm.size(); i++)
        {
            (*MyDataLayer).thin(vec, newSearchTerm[i]);
        }
        while(vec.size() > 1)
        {
            printCompSci(vec);
            cout << "There are multiple scientists that match those criteria."<<endl;
            cout << "Please type in a more specific term:"<<endl;
            cin.ignore();
            getline(cin, term);
            newSearchTerm = explode(term, ' ');
            for(unsigned int i = 0; i < newSearchTerm.size(); i++)
            {
                (*MyDataLayer).thin(vec, newSearchTerm[i]);
            }
        }
        if(vec.size() == 1)
        {
            vector<computer> result;
            result = (*MyDataLayer).getConnections(vec[0]);
            cout << vec[0].field(1) <<" Is connected to the following computers: "<< endl;
            printComputer(result);
        }
    }

    void addConnection()
    {
        vector<ComputerScientist> vec;
        cout << "Please enter the name or identifying qualifier for the Scientist:"<<endl;
        string term;
        cin.ignore();
        getline(cin, term);
        vector <string> newSearchTerm = explode(term, ' ');
        (*MyDataLayer).Search(vec,term);

        for(unsigned int i = 0; i < newSearchTerm.size(); i++)
        {
            (*MyDataLayer).thin(vec, newSearchTerm[i]);
        }
        while(vec.size() > 1)
        {
            printCompSci(vec);
            cout << "There are multiple scientists that match those criteria."<<endl;
            cout << "Please type in a more specific term:"<<endl;
            cin.ignore();
            getline(cin, term);
            newSearchTerm = explode(term, ' ');
            for(unsigned int i = 0; i < newSearchTerm.size(); i++)
            {
                (*MyDataLayer).thin(vec, newSearchTerm[i]);
            }
        }

        vector<computer> vect;
        cout << "Please enter the name or identifying qualifier for the Computer:"<<endl;
        cin.ignore();
        getline(cin, term);
        newSearchTerm = explode(term, ' ');
        (*MyDataLayer).Search(vect,term);

        for(unsigned int i = 0; i < newSearchTerm.size(); i++)
        {
            (*MyDataLayer).thin(vect, newSearchTerm[i]);
        }
        while(vect.size() > 1)
        {
            printComputer(vect);
            cout << "There are multiple Computers that match those criteria."<<endl;
            cout << "Please type in a more specific term:"<<endl;
            cin.ignore();
            getline(cin, term);
            vector <string> newSearchTerm = explode(term, ' ');
            for(unsigned int i = 0; i < newSearchTerm.size(); i++)
            {
                (*MyDataLayer).thin(vect, newSearchTerm[i]);
            }
        }
        if(vect.size() == vec.size() && vec.size() == 1)
        {
            (*MyDataLayer).AddConnection(vec[0],vect[0]);
        }
    }
    
    /*********************************************************************************
     *                      COMPUTER DATABASE SECTION
     * *******************************************************************************/
    
    /************************************************
     * _computer
     * the computer database menu
     * ***********************************************/
    void _computer()
    {
        while (true)
        {
            cout << "This is a Computer database." << endl;
            cout << "----- 1 to add an entry." << endl;
            cout << "----- 2 to remove entries." << endl;
            cout << "----- 3 to search entries." << endl;
            cout << "----- 4 to list all entries." << endl;
            cout << "----- 5 for sorting options." << endl;
            cout << "----- 6 for connections." << endl;
            cout << "----- Any other to go back." << endl;
            char operation = getChar();
            
            if (operation == '1') addToComputer();
            if (operation == '2') removeComputer();
            if (operation == '3') searchComputer();
            if (operation == '4') printComputer();
            if (operation == '5') sortComputer();
            if (operation == '6') connectComputer();
            else break;
        }
    }
    /************************************************
     * addToComputer();
     * Adds a computer to the database
     * ***********************************************/
    void addToComputer()
    {
        while (true)
        {
            string info[5] = {"the Name","the Year","the Type","if it was built","the Location"};
            vector<string> entering;
            
            for(int i = 0; i < 5; i++)
            {
                cout << "Please enter " << info[i] << " of the computer you're adding.\n Leave blank if no information is to be entered\n";
                char entry[64];
                cin.ignore(256,'\n');
                cin.get(entry,64);
                entering.push_back(string(entry));
                cin.clear();
            }
            for(int i = 0; i < 5; i++)
            {
                for(unsigned int n = 0; n < entering[i].size(); n++)
                {
                    if(entering[i][n] == ',')
                    {
                        entering[i][n] = ' ';
                    }
                }
            }
            (*MyDataLayer).Add(entering);
            cout << "//Computer added." << endl;
            cout << "----- 1 to add another computer." << endl;
            cout << "----- Any other to go back." << endl;
            char operation = getChar();
            if (operation == '1')addToComputer();
            else break;
        }
    }
    
    /************************************************
     * SearchComputer
     * Searches and prints the database for computers
     * ***********************************************/
    void searchComputer()
    {
        cout << "Please enter a Name, Type, Location or Year to search for." << endl;
        string term;
        //cin.ignore(10000,'\n');
        getline(cin, term);
        vector <string> newSearchTerm = explode(term, ' ');
        vector<computer> vec;
        (*MyDataLayer).Search(vec,term);

        for(unsigned int i = 0; i < newSearchTerm.size(); i++)
        {
            (*MyDataLayer).thin(vec, newSearchTerm[i]);
        }
        //cin.clear();
        //cin.ignore(10000,'\n');

        printComputer(vec);
    }


    /************************************************
     * printComputer
     * prints to the stdout
     * ***********************************************/
    void printComputer(vector<computer> list)
    {
        cout << endl;
        cout <<"______________________________"<<endl;
        for(unsigned int i = 0; i < list.size(); i++)
        {
            cout << list[i] << endl;
            cout <<"______________________________"<<endl;
        }
        cout << endl;
        cout << "***********************************" << endl;
        cout << "        "<<list.size()<< " matching entries!"<<endl;
        cout << "***********************************" << endl << endl;;
    }
    
    void printComputer()
    {
        vector<computer> vec;
        (*MyDataLayer).GetAll(vec);
        printComputer(vec);
    }
    
    /************************************************
     * Sets Sorting Options
     * ***********************************************/
    void sortComputer()
    {
        while (true)
        {
            cout << "Sort alphabetically or alphanumeracally by:" << endl;
            cout << "Name, year, type or location." << endl;
            cout << "----- 1 Name." << endl;
            cout << "----- 2 Year." << endl;
            cout << "----- 3 Type." << endl;
            cout << "----- 4 Location." << endl;
            cout << "----- Any other to go back." << endl;
            char operation = getChar();
            if (operation == '1') {} else
                if (operation == '2') {} else
                    if (operation == '3') {} else
                        if (operation == '4') {} else
                            break;
        }
    }
    
    /*********************************************************************
     * RemoveCompsci()
     * Asks for a name to remove
     * removes it
     ********************************************************************/
    void removeComputer()
    {
        string name;
        vector<computer> comp;
        cout << "Please enter the name or characteristic of the computer to remove" << endl;
        cin >> name;
        (*MyDataLayer).Search(comp,name);
        while(comp.size() > 1)
        {
            printComputer(comp);
            cout << "There is ambiguity in your choice, please type in a distinct idenifier" << endl;
            cin >> name;
            (*MyDataLayer).thin(comp,name);
        }
        cout << comp[0];
        cout << "Are you sure you wish to delete the above entry? (y/n)" << endl;
        char ent;
        ent = getchar();
        if(ent == 'y' || ent == 'Y')
        {
            (*MyDataLayer).remove(comp[0]);
        }
    }
    
    void connectComputer()
    {
        while (true)
        {
            cout << "Do you want to search connections or add a new connection?" << endl;
            cout << "----- 1 Search connections" << endl;
            cout << "----- 2 Add a new connection" << endl;
            cout << "----- Any other to go back." << endl;
            char operation = getChar();
            if (operation == '1') searchConnectionComputer();
            if (operation == '2') addConnection();
            break;
        } 
    }

    void searchConnectionComputer()
    {

        vector<computer> vec;
        cout << "Please enter the name or identifying qualifier for the Computer:"<<endl;
        string term;
        cin.ignore();
        getline(cin, term);
        vector <string> newSearchTerm = explode(term, ' ');
        (*MyDataLayer).Search(vec,term);

        for(unsigned int i = 0; i < newSearchTerm.size(); i++)
        {
            (*MyDataLayer).thin(vec, newSearchTerm[i]);
        }
        while(vec.size() > 1)
        {
            printComputer(vec);
            cout << "There are multiple computers that match those criteria."<<endl;
            cout << "Please type in a more specific term:"<<endl;
            cin.ignore();
            getline(cin, term);
            newSearchTerm = explode(term, ' ');
            for(unsigned int i = 0; i < newSearchTerm.size(); i++)
            {
                (*MyDataLayer).thin(vec, newSearchTerm[i]);
            }
        }
        if(vec.size() == 1)
        {
            vector<ComputerScientist> result;
            result = (*MyDataLayer).getConnections(vec[0]);
            cout << vec[0].field(1) <<" Is connected to the following Scientist: "<< endl;
            printCompSci(result);
        }
    }

    /*****************
     * ~MaGiC~
     * ****************/
    void magic(){
            cout << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "Welcome to ~MaGiC~" << endl;
            cout << "Please maximize the size of your command terminal for best effect." <<endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "Please make a selection" << endl << endl;
            cout << "1. Magic David. \n";
            cout << "2. Magic Sverrir. \n";
            cout << "Anything else to go back." << endl;

        while(true)
        {
            char input;
            cin >> input;
            if(input == '1'){
                magicDavid();
            } else
            if(input == '2'){
                magicSverrir();
            } else
            break;
            cout << endl << endl << "Please make another selection (1,2) or press anything else to return\n";
        }
    }
};
#endif // UI_H
