#ifndef GAMELOOP_HPP_
#define GAMELOOP_HPP_
#include <thread>
#include <string>
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
public:
    unordered_map<char, array<int,2>> lookup; 
    unordered_map<char, string> effect; 
    Gameloop(int theGame_mode);
    ~Gameloop();
    int run();
    bool intersection(int pos_x, int pos_y, int **themap, bool the_first_move);
};

#endif 