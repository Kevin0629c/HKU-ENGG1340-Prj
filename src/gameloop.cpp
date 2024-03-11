#include "gameloop.hpp"
#include "helpers.hpp"
#include "maze2D.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>

using namespace std;

Timer::Timer(bool* thePis_writing, int theRow, int theCol)
{
    time = 0;
    paused_time = 0;
    is_writing = thePis_writing;
    timer_row = theRow;
    timer_col = theCol;
}

void Timer::start() {
    is_running = true;
    timer = thread(&Timer::job, this);
}

void Timer::pause() {
    is_running = false;
    paused_time = time;
    stop();
}

string Timer::stop() {
    is_running = false;
    if (timer.joinable()) {
        timer.join();
    }
    time = 0;
    return to_string(time);
}

Timer::~Timer() {
    time = 0;
    paused_time = 0;
    stop();
}

void Timer::job() {
    auto start_time = chrono::system_clock::now() - chrono::duration<double>(paused_time);
    while (is_running) {
        if (!*is_writing) {
            chrono::duration<float> time_elapsed_seconds = chrono::system_clock::now() - start_time;
                if (time_elapsed_seconds.count() - time > 0) {
                    time = time_elapsed_seconds.count();
                    cout << "\033[" << timer_row << ";" << timer_col << "H[" << fixed << setprecision(2) << time << "s]" << flush;
                }
        }
    }
    auto time_elapsed = chrono::system_clock::now() - start_time;
    time = time_elapsed.count();
}



Gameloop::Gameloop(int theGame_mode)
{
    lookup = {
        {char('w'), {0, -1}},
        {char('a'), {-1, 0}},
        {char('s'), {0, 1}},
        {char('d'), {1, 0}},
    };
    game_mode = theGame_mode;
}

Gameloop::~Gameloop()
{
}

int Gameloop::run()
{
    int winCols = getWinCols();
    int winRows = getWinRows();
    int position[2] = {1, 1}; //row / col
    char input;
    // cout << "winCols: " << winCols << endl;
    // cout << "winRows: " << winRows << endl;
    clearScreen();
    Maze2D maze(winCols / 2 - 2, (winRows % 2 == 0 ? winRows + 1 : winRows ) - 2, 0);
    maze.printMap();
    maze.map2D;
    while (true)
    {
        char input = getch();
        if ( maze.map2D[position[0] + lookup[input][1]][position[1] + lookup[input][0]] != 0 ){
            printAt( 2*position[1], position[0], maze.glyphs[8]); 
            maze.editMap(position[0], position[1], 8);
            position[0] = position[0] + lookup[input][1];
            position[1] = position[1] + lookup[input][0];
            if (maze.map2D[position[0]][position[1]] == 2){
                cout << "you win the game" << endl;
                break;
            }
            if (maze.map2D[position[0]][position[1]] == 3){
                
            }
            printAt( 2*position[1], position[0], maze.glyphs[9]);
            maze.editMap(position[0], position[1], 9);
        }
        
    }
    bool is_writing = false;
    Timer timer(&is_writing, 0, 0);
    timer.start();
    this_thread::sleep_for(chrono::seconds(1));
    timer.pause();
    this_thread::sleep_for(chrono::seconds(1));
    timer.start();
    this_thread::sleep_for(chrono::seconds(1));
    timer.stop();

    clearScreen();
    cout << "Maze dimension in chars: " << maze.result_width << "x" << maze.result_height << endl;
    
    return 0;
}

