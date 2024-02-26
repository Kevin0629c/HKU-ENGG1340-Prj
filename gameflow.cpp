#include "gameflow.hpp"
#include "helpers.hpp"
#include "termcolor.hpp"
using namespace std;

gameflow::gameflow(int theWidth, int theHeight, int theSeed)
{
    width = theWidth;
    height = theHeight;
    seed = theSeed;
    map2D = new int *[theWidth];

    for (int i = 0; i < theWidth; ++i)
    {
        map2D[i] = new int[theHeight];
    }
}

void gameflow::printGame()
{
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            cout << map2D[i][j] << " ";
        }
        cout << endl;
    }
}