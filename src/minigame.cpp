#include "minigame.hpp"
#include "helpers.hpp"
#include <iostream>

using namespace std;

Minigame::Minigame(int theGame_mode)
{
    game_mode = theGame_mode;
}

Minigame::~Minigame()
{
}

int Minigame::run()
{
    int winCols = getWinCols();
    int winRows = getWinRows();

    cout << "╔";
    for (int i = 0; i < winCols - 2; i++) 
    {
        cout << "═";
    }
    cout << "╗" << endl;
    
    for (int i = 1; i < winRows - 2; i++) {
        cout << "║" ;
        for (int j = 1; j < winCols - 1; j++){
            cout << " ";
        }
        cout << "║" << endl;
    }

    cout << "╚";
    for (int i = 0; i < winCols - 2; i++) 
    {
        cout << "═";
    }
    cout << "╝" << endl;
    char c = getch();
    return 0;
}