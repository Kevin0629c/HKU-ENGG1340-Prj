#include <stdio.h>
#include <string>
#include "terminalHelpers.h"
using namespace std;

int main() {
    printf("Hello World!\n");
    char c = getch();
    clear_screen();
    printf("You pressed %c!\n", c);
    return 0;
}