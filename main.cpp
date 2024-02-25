#include <iostream>
#include <string>
#include "terminalHelpers.hpp"
#include "termcolor.hpp"

using namespace std;

int main() {
    cout << termcolor::red << "Hello World!" << endl;
    char c;
    c = getch();
    clear_screen();
    cout << "You pressed " << c << "!" << endl;
    return 0;
}