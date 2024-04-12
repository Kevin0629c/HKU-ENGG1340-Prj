#include <iostream>
#include <string>
#include "helpers.hpp"
#include "gameloop.hpp"
#include "pagedmenu.hpp"
#include "loader.hpp"
#include <chrono>

using namespace std;

int main()
{
    // check terminal size
    if (getWinRows() < 0 || getWinCols() < 0)
    {
        cout << "Terminal size too small. Please resize to at least 50x20." << endl;
        return 1;
    }

    cursorHide();
    toggleEcho();

    Gameloop game;
    State gameState;
    Loader loader;
    int game_result = -1;
    while (true)
    {
        PagedMenu menu;                    //Linkage with pagedmenu setting requried
        int response = menu.displayMenu();
        clearScreen();
        if (response == 2)               // System mechanism for handling user's input
        {
            return 1; // Quit the game
        }
        else if (response == 1)
        {
            game_result = game.run(loader.loadState());
        }
        else 
        {
            game_result = game.run(gameState);
        }

        if (game_result == 0)
        {
            cout << "You LOSE!!!" << endl;
            // Handle lost state
        }
        else if (game_result == 1)
        {
            cout << "You WIN!!!" << endl;
            // Handle win state
        }
        
    }

    cursorShow();

    return 0;
}