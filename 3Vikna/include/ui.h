#ifndef UI_H
#define UI_H

#include <iostream>
#include "ComputerScientist.h"
#include "magicaldataclass.h"
#include "computer.h"

using namespace std;
class UI{
    public:
    UI(){
        MyDataLayer = new MagicalDataClass("CompDataBase.sqlite");
    }

    /************************************************
     * start
     * actually runs the program
     * ***********************************************/
    void start(){
        while (true) {
            cout << "Which database would you like to access?" << endl;
            cout << "----- 1 Computer scientists." << endl;
            cout << "----- 2 Computers." << endl;
            cout << "----- q to quit" << endl;
            char operation = getChar();
    
            if (operation == '1')compSci(); else
            if (operation == '2') _computer(); else
            if (operation == 'q' || operation == 'Q') break;
            else cout << "Please choose a valid option." << endl;
        }
    }

    private:
    MagicalDataClass* MyDataLayer;
    

    /************************************************
     * getChar()
     * get's a single character form Stdin
     * ***********************************************/
    char getChar() { 
        char c;
        cin >> c;
        return c;
    }


    /************************************************
     * compSci()
     * The computer scientist database menu
     * ***********************************************/
    void compSci() {
        while (true) {
            cout << "This is a Computer Scientist database." << endl;
            cout << "----- 1 to add an entry." << endl;
            cout << "----- 2 to search entries." << endl;
            cout << "----- 3 to list all entries." << endl;
            cout << "----- 4 for sorting options." << endl;
            cout << "----- Any other to go back." << endl;
            char operation = getChar();

            if (operation == '1') addToCompSci();
            if (operation == '2') searchCompSci();
            if (operation == '3') printCompSci();
            if (operation == '4') sortCompSci();
            else break;
        }

    }

    /************************************************
     * addToCompSci
     * Adds a name to the computer scientist databse
     * ***********************************************/
    void addToCompSci() {
        while (true) {
            string info[8] = {"First name","Middle name(s)","Last Name","Gender","Birth Year","Death Year","Nationality","Fields of profession"};
            vector<string> entering;

            for(int i = 0; i < 8; i++){
                cout << "Please enter the " << info[i] << " of the scientist you're adding.\n Leave blank if no information is to be entered\n";
                char entry[64];
                cin.ignore(256,'\n');
                cin.get(entry,64);
                entering.push_back(string(entry));
                cin.clear();
            }
            for(int i = 0; i < 8; i++){
                for(unsigned int n = 0; n < entering[i].size(); n++){
                   if(entering[i][n] == ','){
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
            //ToDo: impliment this
        }
    }


    /************************************************
     * SearchCompSci
     * Asks the database for a vector of all scientist matching a term
     * Prints it to StdOut
     * ***********************************************/

    void searchCompSci() {
            cout << "Please enter the name you wish to search for." << endl;
            string term;
            cin >> term;
            vector<ComputerScientist> vec;
            (*MyDataLayer).Search(vec,term);
            printCompSci(vec);
    }
    /************************************************
     * PrintCompSci
     * prints a vector
     * ***********************************************/
    void printCompSci(vector<ComputerScientist> list) {
        cout << endl;
        cout <<"______________________________"<<endl;
        for(unsigned int i = 0; i < list.size(); i++){
            cout << list[i] << endl;
            cout <<"______________________________"<<endl;
        }
        cout << endl;
        cout << "***********************************" << endl;
        cout << "        "<<list.size()<< " matching entries!"<<endl;
        cout << "***********************************" << endl << endl;
    }

    void printCompSci(){
        vector<ComputerScientist> vec;
        (*MyDataLayer).GetAll(vec);
        printCompSci(vec);
    }

    /************************************************
     * sortCompSci
     * Changes the sorting pattern
     * ***********************************************/
    void sortCompSci() {
        while (true) {
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
/*********************************************************************************
 *                      COMPUTER DATABASE SECTION
 * ********************************************************************************/

    /************************************************
     * _computer
     * the computer database menu
     * ***********************************************/
    void _computer() {
        while (true) {
            cout << "This is a Computer database." << endl;
            cout << "----- 1 to add an entry." << endl;
            cout << "----- 2 to search entries." << endl;
            cout << "----- 3 to list all entries." << endl;
            cout << "----- 4 for sorting options." << endl;
            cout << "----- Any other to go back." << endl;
            char operation = getChar();

            if (operation == '1') addToComputer();
            if (operation == '2') searchComputer();
            if (operation == '3') printComputer();
            if (operation == '4') sortComputer();
            else break;
        }
    }
    /************************************************
     * addToComputer();
     * Adds a computer to the database
     * ***********************************************/
    void addToComputer() {
        while (true) {
            string info[5] = {"the Name","the Year","the Type","if it was built","the Location"};
            vector<string> entering;

            for(int i = 0; i < 5; i++){
                cout << "Please enter " << info[i] << " of the computer you're adding.\n Leave blank if no information is to be entered\n";
                char entry[64];
                cin.ignore(256,'\n');
                cin.get(entry,64);
                entering.push_back(string(entry));
                cin.clear();
            }
            for(int i = 0; i < 5; i++){
                for(unsigned int n = 0; n < entering[i].size(); n++){
                   if(entering[i][n] == ','){
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
    void searchComputer() {
        cout << "Please enter a Name, Type, Location or Year to search for." << endl;
        string term;
        cin >> term;
        vector<computer> vec;
        (*MyDataLayer).Search(vec,term);
        printComputer(vec);
    }

    /************************************************
     * printComputer
     * prints to the stdout
     * ***********************************************/
    void printComputer(vector<computer> list) {
        cout << endl;
        cout <<"______________________________"<<endl;
        for(unsigned int i = 0; i < list.size(); i++){
            cout << list[i] << endl;
            cout <<"______________________________"<<endl;
        }
        cout << endl;
        cout << "***********************************" << endl;
        cout << "        "<<list.size()<< " matching entries!"<<endl;
        cout << "***********************************" << endl << endl;;
    }

    void printComputer() {
        vector<computer> vec;
        (*MyDataLayer).GetAll(vec);
        printComputer(vec);
    }

    /************************************************
     * Sets Sorting Options
     * ***********************************************/
    void sortComputer() {
        while (true) {
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
};
#endif // UI_H
