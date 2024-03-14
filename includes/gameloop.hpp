#ifndef GAMELOOP_HPP_
#define GAMELOOP_HPP_
#include "maze2D.hpp"
#include <thread>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Timer
{
    thread timer;
    int timer_row;
    int timer_col;
    bool is_running;
    double paused_time;
    void job();
public:
    double time;
    bool* is_writing;
    Timer(bool* thePis_writing, int theRow, int theCol);
    ~Timer();
    void start();
    void pause();
    string stop();
};



class Gameloop
{
    int game_mode;
    bool choice;
    char input;
    char playerinput;
    char playerinput2;
    unordered_map<char, array<int,2>> lookup; 
    unordered_map<char, string> effect; 
    vector<int> resolvelist;
    vector<int> checkwall(char playerinput, int* position, int** themap, int width, int height, string detector);
    bool intersection(int pos_x, int pos_y, int **themap, bool the_first_move);
public:
    Gameloop(int theGame_mode);
    ~Gameloop();
    int run();
    
};

#endif 