#include "gameloop.hpp"
#include "helpers.hpp"
#include "maze2D.hpp"

using namespace std;

Gameloop::Gameloop(int theGame_mode)
{
    game_mode = theGame_mode;
}

Gameloop::~Gameloop()
{
}

int Gameloop::run()
{
    int winCols = getWinCols();
    int winRows = getWinRows();
    Maze2D maze(winCols, winRows, 0);
    maze.printMap();
    return 0;
}