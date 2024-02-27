#include "minigame.hpp"
#include "helpers.hpp"

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
    char c = getch();
    return 0;
}