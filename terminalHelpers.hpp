#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
using namespace std;

void print_at(int x, int y, string c) {
    // Save current cursor position
    cout << "\033[s";
    // Move cursor to x, y
    cout << "\033[" << y << ";" << x << "H";
    // Print character
    cout << c;
    // Restore saved cursor position
    cout << "\033[u" << flush;
}

void clear_screen() {
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    cout << "\033[2J\033[H";
}

// Get a single character from stdin without waiting for enter, by changing the terminal settings
char getch() {
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