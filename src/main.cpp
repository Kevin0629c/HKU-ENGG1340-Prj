#define MINIAUDIO_IMPLEMENTATION

#include <iostream>
#include <string>
#include "helpers.hpp"
#include "gameloop.hpp"
#include "pagedmenu.hpp"
#include "miniaudio.h"
#include <chrono>

using namespace std;

// audio engine and result objects
ma_result result;
ma_engine engine;

int main()
{
    // initialize audio engine
    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        return -1;
    }

    // check terminal size
    if (getWinRows() < 0 || getWinCols() < 0)
    {
        cout << "Terminal size too small. Please resize to at least 50x20." << endl;
        return 1;
    }

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

    // Use the following code to play a sound 
    // ma_engine_play_sound(&engine, "../resources/bop.wav", NULL);

    cout << "Press Enter to quit...";
    getchar();

    // uninitialize audio engine
    ma_engine_uninit(&engine);
    return 0;
}
