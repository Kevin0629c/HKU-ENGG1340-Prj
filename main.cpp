#include <iostream>
#include <string>
#include "helpers.hpp"
#include "maze2D.hpp"

using namespace std;

int main()
{
    // cout << termcolor::red << "Hello World! Press anything to continue" << endl;
    // char inputted_char = getch();
    // clearScreen();
    // cout << "You pressed " << inputted_char << "!" << endl;

    Maze2D maze(20, 15, 0);
    maze.printGame();
    return 0;
}
