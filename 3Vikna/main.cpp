#include "include/ComputerScientist.h"
#include "include/FileData.h"
#include <iostream>
#include <string>
using namespace std;

char getChar();

void addToList();
void searchList();
void printList();

char getChar(){
    char c;
    cin >> c;
    return c;
}

void addToList() {
    while (true) {
        cout << "Enter name, gender, year of birth, year of death(if applicable)." << endl;
        cout << "In this format: Blaise Pascal,Male,1623,1662." << endl;
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
    while (true) {
        cout << "What do you want to search for?" << endl;
        cout << "----- 1 Name." << endl;
        cout << "----- 2 Sex." << endl;
        cout << "----- 3 Year of birth." << endl;
        cout << "----- 4 Year of death." << endl;
        cout << "----- Any other to go back." << endl;
        char operation = getChar();
        if (operation == '1') break;
        if (operation == '2') break;
        if (operation == '3') break;
        if (operation == '4') break;
        else  break;
        //ToDo: impliment this
    }
}

void printList() {
    cout << "//Prints everything";
}

void sortOptions(int &howToSort) {
    while (true) {
        cout << "Sort alphabetically or alphanumeracally by:" << endl;
        cout << "First name, last name, sex, year of birth or year of death." << endl;
        cout << "----- 1 First name." << endl;
        cout << "----- 2 Middle name." << endl;
        cout << "----- 3 Last name." << endl;
        cout << "----- 4 Gender." << endl;
        cout << "----- 5 Year of birth." << endl;
        cout << "----- 6 Year of death." << endl;
        cout << "----- Any other to go back." << endl;
        char operation = getChar();
        if (operation == '1') howToSort = 1;
        if (operation == '2') howToSort = 2;
        if (operation == '3') howToSort = 3;
        if (operation == '4') howToSort = 4;
        if (operation == '5') howToSort = 5;
        if (operation == '6') howToSort = 6;
        else break;
    }
}

int main()
{
    FileData F("LOL.txt");
    F.Save("TESTING.txt");
    int howToSort;

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
        if (operation == '3') printList();
        if (operation == '4') sortOptions(howToSort);
        if (operation == 'q' || operation == 'Q');

        else break;
    }
    return 0;
}
