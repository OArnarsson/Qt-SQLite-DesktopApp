#ifndef UI_H
#define UI_H

#include <iostream>
#include "ComputerScientist.h"
#include "magicaldataclass.h"

using namespace std;
class UI{
    public:
    UI(){
        MyDataLayer = new MagicalDataClass("CompSci_Formatted.txt");
    }
    void start(){
        while (true) {
               cout << "This is a Computer Scientist database." << endl;
               cout << "----- 1 to add an entry." << endl;
               cout << "----- 2 to search entries." << endl;
               cout << "----- 3 to list all entries." << endl;
               cout << "----- 4 for sorting options." << endl;
               cout << "----- Q to quit." << endl;
               char operation = getChar();

               if (operation == '1') addToList();
               if (operation == '2') searchList();
               if (operation == '3') PrintAll();
               if (operation == '4') sortOptions();
               if (operation == 'q' || operation == 'Q') break;
           }
    }

    private:
    MagicalDataClass* MyDataLayer;
    char getChar(){
        char c;
        cin >> c;
        return c;
    }

    void addToList() {
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
            if (operation == '1')addToList();
            else break;
            //ToDo: impliment this
        }
    }

    void searchList() {
            cout << "Please enter the name you wish to search for" << endl;
            /*cout << "What do you want to search for?" << endl;
            cout << "----- 1 Name." << endl;
            cout << "----- 2 Gender." << endl;
            cout << "----- 3 Year of birth." << endl;
            cout << "----- 4 Year of death." << endl;
            cout << "----- Any other to go back." << endl;
            char operation = getChar();
            if (operation == '1') break;
            if (operation == '2') break;
            if (operation == '3') break;
            if (operation == '4') break;
            else  break;*/
            string term;
            cin >> term;
            printList((*MyDataLayer).Search(term));
    }

    void printList(vector<ComputerScientist> list) {
        cout << "***********************************" << endl;
        cout << "        "<<list.size()<< " matching entries!"<<endl;
        cout << "***********************************" << endl;
        for(unsigned int i = 0; i < list.size(); i++){
            cout << list[i] << endl;
            cout <<"______________________________"<<endl;
        }
        cout << endl;
    }

    void PrintAll(){
        printList((*MyDataLayer).GetAll());
    }

    void sortOptions() {
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
};
#endif // UI_H
