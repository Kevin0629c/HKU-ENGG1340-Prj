#ifndef GAMEFLOW_HPP_
#define GAMEFLOW_HPP_

#include <iostream>
#include <string>
// #include <unordered_map>
using namespace std;

template <typename T>
class Map2D {
public:
    Map2D(int width, int height) : width_(width), height_(height) {
        data_.resize(width_, std::vector<T>(height_));
    }

    T& operator()(int row, int col) {
        return data_[row][col];
    }

private:
    int width_;
    int height_;
    std::vector<std::vector<T>> data_;
};

class Gameflow
{

    /* ------------- Params ------------- */
    int width;
    int height;
    int seed;

    unordered_map<int, string> glyphs;
    /* --------------- Gen -------------- */
    int **grid2D;
    unordered_map<int, unordered_map<int, bool> > transfers;

public:
    Gameflow(int theWidth, int theHeight, int theSeed); // Constructor

    int **map2D;
    int result_width;
    int result_height;
    void startGame();
    void printGame();
    void printTransfers();
    void endGame();

    ~Gameflow(); // Destructor

    void kruskalize();
    void generateMaze();
};

#endif