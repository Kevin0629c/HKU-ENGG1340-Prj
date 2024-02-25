#include <iostream>
#include <string>
#include "terminalHelpers.hpp"
#include "termcolor.hpp"

using namespace std;

int main() {
    cout << termcolor::red << "Hello World! Press anything to continue" << endl;
    char inputted_char = getch();
    clearScreen();
    cout << "You pressed " << inputted_char << "!" << endl;
    return 0;
}