#include <iostream>
#include <string>
#include "helpers.hpp"
#include "termcolor.hpp"
#include "gameflow.hpp"

using namespace std;

int main()
{
    // cout << termcolor::red << "Hello World! Press anything to continue" << endl;
    // char inputted_char = getch();
    // clearScreen();
    // cout << "You pressed " << inputted_char << "!" << endl;
    gameflow newGame = {10, 10, 0};
    newGame.printGame();
    return 0;
}