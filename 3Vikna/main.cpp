#include "include/ComputerScientist.h"
#include "include/FileData.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
     FileData F("LOL");
     ComputerScientist Turing("Alan","","Turing","male",1889,1934);
     F.Add(Turing);
    return 0;
}
