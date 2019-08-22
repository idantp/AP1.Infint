#include <iostream>
#include <cstring>
#include <cstdlib>

#include "InfInt.h"

using namespace std;

// make sure the programs does not take too long to run!
int main() {
    InfInt s = "5";
    InfInt s1 = "-13";
    cout << (s & s1) << endl;
    cout << (s | s1) << endl;
    cout << (s ^ s1) << endl;

    return 0;
}