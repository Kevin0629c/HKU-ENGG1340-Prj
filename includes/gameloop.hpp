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

class Movement
{
    int width;
    int height;
    int playerW;
    int playerA;
    int playerS;
    int playerD;
    int preplayerx;
    int preplayery;
    int endx;
    int endy;
public:
    Movement(int **themap, int result_width, int result_height);
    ~Movement();
    string themove;
    int **maze1;
    int playerx;
    int playery;
    void playerloc();
    void playerinput();
    bool endgame();
    void phymove(string themove);
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