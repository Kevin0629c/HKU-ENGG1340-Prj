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

    /* ------------- Params ------------- */
    unordered_map<int, string> glyphs;  
    /* ------------ Info data ----------- */
    int **map2D; // 2D array of maze, represented by integers. 
        // 0 is wall
        // 1 is space
        // 2 is end
        // 3 is portal
        // 9 is player
        // 8 is tail
    int result_width; // width of maze printed
    int result_height; // height of maze printed

    /* ------------ Functions ----------- */
    void printGame();

    ~Maze2D(); // Destructor
};

#endif