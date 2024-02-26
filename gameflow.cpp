#include "gameflow.hpp"
#include "helpers.hpp"
#include "termcolor.hpp"
using namespace std;

/* ----------- Constructor ---------- */
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

/* ------------ Functions ----------- */
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

/* ----------- Destructor ----------- */
gameflow::~gameflow()
{
    for (int i = 0; i < width; ++i)
    {
        delete[] map2D[i];
    }
    delete[] map2D;
}