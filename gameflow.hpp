#ifndef GAMEFLOW_HPP_
#define GAMEFLOW_HPP_

#include <iostream>
#include <string>
// #include <unordered_map>
using namespace std;

class Gameflow
{

    int width;
    int height;
    int seed;
    int **map2D;

    unordered_map<int, string> glyphs;

    int **grid2D;
    unordered_map<int, unordered_map<int, bool> > transfers;

public:
    Gameflow(int theWidth, int theHeight, int theSeed); // Constructor

    void startGame();
    void printGame();
    void printTransfers();
    void endGame();

    ~Gameflow(); // Destructor

    void kruskalize();
    void generateMaze();
};

#endif