#ifndef GAMEFLOW_HPP_
#define GAMEFLOW_HPP_

#include <iostream>
#include <string>
using namespace std;

class gameflow
{
    int width;
    int height;
    int seed;
    int **map2D;

public:
    gameflow(int theWidth, int theHeight, int theSeed); // Constructor

    void startGame();
    void printGame();
    void endGame();
};

#endif