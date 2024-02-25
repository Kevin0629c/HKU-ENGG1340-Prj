#include <iostream>
#include <string>
#include "terminalHelpers.hpp"
#include "termcolor.hpp"

using namespace std;

int main() {
    cout << termcolor::red << "Hello World! Press anything to continue" << endl;
    char c;
    c = getch();
    clearScreen();
    cout << "You pressed " << c << "!" << endl;
    return 0;
}