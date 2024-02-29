#ifndef GAMELOOP_HPP_
#define GAMELOOP_HPP_
#include <thread>
#include <string>

using namespace std;

class Timer
{
    thread timer;
    int timer_row;
    int timer_col;
    bool* is_writing;
    bool is_running;
    double paused_time;
    void job();
public:
    double time;
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
    Gameloop(int theGame_mode);
    ~Gameloop();
    int run();
};

#endif 