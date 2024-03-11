#include <iostream>
#include <string>
#include "helpers.hpp"
#include "gameloop.hpp"
#include "pagedmenu.hpp"
#include "colors.hpp"
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

    cout << CURSOR_HIDE;

    Gameloop game(0);
    int game_result = game.run();

    /*
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

   cout << CURSOR_SHOW;

    return 0;
}
