#include "include/ComputerScientist.h"
#include "include/FileData.h"
#include <iostream>
#include <string>
using namespace std;

void addToList();
void searchList();
void printList();

char getChar(){
    char c;
    cin >> c;
    return c;
}

void addToList(){

}

void searchList() {

}

void printList() {

}

int main()
{
    FileData F("LOL.txt");
    F.Save("TESTING.txt");

    while (true) {
        cout << "This is a Computer Scientist database." << endl;
        cout << "Press 1 to add an entry." << endl;
        cout << "Press 2 to search entries." << endl;
        cout << "Press 3 to list all entries" << endl;
        cout << "Press Q button to quit." << endl;
        char operation = getChar();

        if (operation == '1') addToList();
        if (operation == '2') searchList();
        if (operation == '3') printList();
        if (operation == 'q' || operation == 'Q') break;
    }
    return 0;
}
