#ifndef GAMEFLOW_HPP_
#define GAMEFLOW_HPP_

#include <iostream>
#include <string>
using namespace std;

class Gameflow
{
    int width;
    int height;
    int seed;
    int **map2D;
    unordered_map<int, unordered_map<int, bool>> transfers;

public:
    Gameflow(int theWidth, int theHeight, int theSeed); // Constructor

    void startGame();
    void printGame();
    void endGame();
    void kruskalize();
    void printTransfers();

    ~Gameflow(); // Destructor
};

#endif