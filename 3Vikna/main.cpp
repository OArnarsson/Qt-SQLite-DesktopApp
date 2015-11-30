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
    char c; cin >> c; return c;
}

void addToList() {

}

void searchList() {

}

void printList() {

}

void sortOptions() {

}

int main()
{
    FileData F("LOL.txt");
    F.Save("TESTING.txt");

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
        if (operation == '4') sortOptions();
        if (operation == 'q' || operation == 'Q') break;
    }
    return 0;
}
