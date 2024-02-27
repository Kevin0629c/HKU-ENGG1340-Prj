#ifndef MAZE2D_HPP_
#define MAZE2D_HPP_

#include <iostream>
#include <string>
// #include <unordered_map>
using namespace std;

class Maze2D
{

    /* ------------- Params ------------- */
    // IMPORTANT: the result width is always width + 1 due to calculation differences
    int width; 
    int height;
    int seed;

    /* ------------- Private ------------ */
    int **grid2D;
    unordered_map<int, unordered_map<int, bool> > transfers;

    void printTransfers();
    void kruskalize();
    void generateMaze();
public:
    Maze2D(int theWidth, int theHeight, int theSeed); // Constructor TODO: GLYPHS

    /* ------------ Info data ----------- */
    unordered_map<int, string> glyphs;
    int result_width;
    int result_height;
    int **map2D;

    /* ------------ Functions ----------- */
    void printGame();

    ~Maze2D(); // Destructor
};

#endif