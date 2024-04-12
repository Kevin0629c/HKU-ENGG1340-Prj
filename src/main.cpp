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
    int winCols = getWinCols();
    int winRows = getWinRows();
    if (winRows < 0 || winCols < 0)
    {
        cout << "Terminal size too small. Please resize to at least 50x20." << endl;
        return 1;
    }

    cursorHide();
    toggleEcho();

    Gameloop game;
    State defaultGame;
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
        if (response == 1)
        {
            State loadedState = loader.loadState();
            if (loadedState.Map2D == nullptr)
            {
                string m = "Loaded file is not a state. Try saving a game by hitting P in-game.";
                printAt(winCols/2 - m.length()/2, winRows/2, m);
                getch();
                continue;
            }
            if (loadedState.winCols == winCols && loadedState.winRows == winRows)
            {
                game_result = game.run(loadedState);
            } else {
                string m = "Map size does not match terminal. Please resize terminal to " + to_string(loadedState.winCols) + "x" + to_string(loadedState.winRows);
                printAt(winCols/2 - m.length()/2, winRows/2, m);
                getch();
            }
        }
        else 
        {
            game_result = game.run(defaultGame);
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