#include "helpers.hpp"
#include <iostream>
#include <string>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
using namespace std;

void cursorHide() {
    cout << "\033[?25l";
}

void cursorShow() {
    cout << "\033[?25h";
}

/*
    Print a string at a specific position on the terminal
    x: x coordinate
    y: y coordinate
    s: string to print
*/
void printAt(int x, int y, string s)
{
    // Move cursor to x, y and print s
    cout << "\033[" << y +1 << ";" << x +1 << "H" << s << flush;
}

/*
    Clear the terminal screen
*/
void clearScreen()
{
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    cout << "\033[2J\033[H";
}

/*
    Get a single character from stdin without waiting for enter, by changing the terminal settings
    Returns the character read
*/
char getch()
{
    // get stdin file descriptor
    int file_desc = STDIN_FILENO;
    // get stdin file settings
    struct termios old_settings, new_settings;
    tcgetattr(file_desc, &old_settings);
    new_settings = old_settings;
    // modifies settings
    new_settings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(file_desc, TCSANOW, &new_settings);
    // read a single byte
    char ch;
    read(file_desc, &ch, 1);
    // set the stdin settings back to before raw modification
    tcsetattr(file_desc, TCSANOW, &old_settings);
    return ch;
}

/*
    Get the number of rows in the terminal
    Returns the number of rows
*/
int getWinRows() {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size.ws_row;
}

/*
    Get the number of columns in the terminal
    Returns the number of columns
*/
int getWinCols() {
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size.ws_col;
}