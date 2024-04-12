#include <iostream>
#include <string>
#include "helpers.hpp"
#include "gameloop.hpp"
#include "pagedmenu.hpp"
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
    while (true)
    {
        PagedMenu menu;                    //Linkage with pagedmenu setting requried
        int response = menu.displayMenu();
        clearScreen();
        if (response == -1)               // System mechanism for handling user's input
        {
            return 1; // Quit the game
        }
        else
        {
            Gameloop game(response);
            int game_result = game.run();
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
    }

    cursorShow();

    return 0;
}

/* V2
    while (true) 
    {
        PagedMenu menu(menu_data);            //Linkage with pagedmenu setting requried
        int response = menu.displayMenu();
        if (response == -1)                   //May change to 0 according pagedmenu
        {                 
            return 0;
        } 
        else 
        {
            Gameloop game(response);
        }
                                
        int game_result = game.run();
        if (game_result == 0) {
            return 0;
            // quit game
        } 
        else if (game_result == 1) {
            cout << "You LOSE!!!" << endl
            // lost
        } 
        else {
            cout << "You WIN!!!" << endl
            // won
        }
    }
*/

/* V1
    while (true) {
        PagedMenu menu(menu_data);
        int response = menu.displayMenu()
        if (response == -1) {
            return 0;
        } else {
            Gameloop game(response);
        }
        int game_result = game.run()
        if (game_result == -1) {
            // quit game
        } else if (game_result == 0) {
            // lost
        } else {
            // won
        }
    }
*/