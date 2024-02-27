#include <iostream>
#include <string>
#include "helpers.hpp"
#include "gameloop.hpp"
#include "pagedmenu.hpp"

using namespace std;

int main()
{
    // check terminal size
    if (getWinRows() < 50 || getWinCols() < 20)
    {
        cout << "Terminal size too small. Please resize to at least 50x20." << endl;
        return 1;
    }

    /*
    while (true) {
        PagedMenu menu(menu_data);
        int response = menu.displayMenu()
        if (response == -1) {
            return 0;
        } else {
            Gameloop game(response);
        }
        game_result = game.run()
        if (game_result == -1) {
            // quit game
        } else if (game_result == 0) {
            // lost
        } else {
            // won
        }
    }
    */
    return 0;
}
