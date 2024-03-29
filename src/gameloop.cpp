#include "gameloop.hpp"
#include "helpers.hpp"
#include "maze2D.hpp"
#include "colors.hpp"
#include "minigame.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <vector>

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
        if (!* is_writing) {
            chrono::duration<float> time_elapsed_seconds = chrono::system_clock::now() - start_time;
                if (time_elapsed_seconds.count() - time > 0.01) {
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
    // lookup: the allowed player movement
    lookup = {  
        {char('w'), {0, -1}},
        {char('a'), {-1, 0}},
        {char('s'), {0, 1}},
        {char('d'), {1, 0}},
    };
    // effect: the effect of breaking wall
    effect = {
        {char('w'), {"||"}},
        {char('a'), {"--"}},
        {char('s'), {"||"}},
        {char('d'), {"--"}},
    };
    game_mode = theGame_mode;
}

Gameloop::~Gameloop()
{
}
// intersection: allow the player to move more smoothly and stop when they arrive the intersection
bool Gameloop::intersection(int pos_x, int pos_y, int **themap, bool the_first_move){
    int num = 0;
    if (themap[pos_y+1][pos_x] == 1 || themap[pos_y+1][pos_x] == 8)
        num++;
    if (themap[pos_y-1][pos_x] == 1 || themap[pos_y-1][pos_x] == 8)
        num++;
    if (themap[pos_y][pos_x+1] == 1 || themap[pos_y][pos_x+1] == 8)
        num++;
    if (themap[pos_y][pos_x-1] == 1 || themap[pos_y][pos_x-1] == 8)
        num++;
    
    if (num >= 3 && the_first_move == false) 
        return 0;
    return 1;
}
// checkwall: allow the player to knowing the wall they going to break down / and showing that with "detector"
vector<int> Gameloop::checkwall(char playerinput, int* position, int** themap, int width, int height, string detector){
    
    // save the wall data into the list that allow the player to change their idea
    vector<int> resolvelist;
    resolvelist.clear();

    for (int i = 1; i < 7; i++) { 
        if ( themap[position[0] + i*lookup[playerinput][1]][position[1] + i*lookup[playerinput][0]] != 2 ) {
            if (position[1] + i*lookup[playerinput][0] != 0 && position[0] + i*lookup[playerinput][1] != 0 && position[1] + i*lookup[playerinput][0] != width -1 && position[0] + i*lookup[playerinput][1] != height -1 ) {
                this_thread::sleep_for(chrono::milliseconds(1));
                resolvelist.push_back(themap[position[0] + i*lookup[playerinput][1]][position[1] + i*lookup[playerinput][0]]);
                // print the wall which the player going to break down with the "detector"
                printAt( 2*(position[1] + i*lookup[playerinput][0]), position[0] + i*lookup[playerinput][1], detector);
            }
            else if (position[1] + i*lookup[playerinput][0] == 0 || position[0] + i*lookup[playerinput][1] == 0 || position[1] + i*lookup[playerinput][0] == width -1 || position[0] + i*lookup[playerinput][1] == height -1 ) {
                return resolvelist;
            }
        }
        else{
            return resolvelist;
        }
    }
    return resolvelist;
}


int Gameloop::run()
{
    int winCols = getWinCols();
    int winRows = getWinRows();
    int position[2] = {1, 1}; //row / col
    char input;
    bool the_first_move;
    bool choice;
    // cout << "winCols: " << winCols << endl;
    // cout << "winRows: " << winRows << endl;
    clearScreen();
    Maze2D maze(winCols / 2 - 2, (winRows % 2 == 0 ? winRows + 1 : winRows ) - 2, 0);
    maze.printMap();
    maze.map2D;
    bool is_writing = false;
    Timer timer(&is_writing, 0, winCols/2 - 7);
    timer.start();
    while (true)
    {
        choice = false;
        char input = getch();
        // check if the player is in the first move or not
        the_first_move = true;
        
        while (intersection(position[1], position[0], maze.map2D, the_first_move)) {
            the_first_move = false;
            // player movement: only stop when there is intersection or wall
            if ( maze.map2D[position[0] + lookup[input][1]][position[1] + lookup[input][0]] != 0 ){
                is_writing = true;
                this_thread::sleep_for(chrono::milliseconds(25));
                // replace the moved place to glyph[8]
                printAt( 2*position[1], position[0], maze.glyphs[8]); // change the moved space 
                maze.editMap(position[0], position[1], 8); // edit the map

                position[0] = position[0] + lookup[input][1]; // move the player
                position[1] = position[1] + lookup[input][0]; // move the player
                printAt( 2*position[1], position[0], maze.glyphs[9]); // change the player location
                is_writing = false;

                // end the game when the player arrive to the "end"
                if (maze.map2D[position[0]][position[1]] == 2){
                    cout << "you win the game" << endl;
                    timer.stop();
                    return 0;
                }

                // start the minigame when the player arrive to the "function"
                if (maze.map2D[position[0]][position[1]] == 3){
                    is_writing = true;
                    this_thread::sleep_for(chrono::milliseconds(1));
                    printAt( 2*position[1], position[0], maze.glyphs[9]); // change the player location
                    maze.editMap(position[0], position[1], 9);
                    is_writing = false;
                    // get into the game

                    // win can get ability to break the wall
                    char playerinput = getch(); //the direction of breaking
                    //chooce the direction of wall breaking
                    while (choice == false) {
                        is_writing = true;
                        // showing the wall going to break
                        resolvelist = checkwall(playerinput, position, maze.map2D, maze.result_width, maze.result_height, maze.glyphs[5]);
                        is_writing = false;
                        // confirm the break
                        char playerinput2 = playerinput;
                        playerinput = getch();
                        
                        if (playerinput == playerinput2) {
                            //breaking wall
                            choice = true;
                            for (int i = 1; i < 7; i++) { 
                                if ( maze.map2D[position[0] + i*lookup[playerinput][1]][position[1] + i*lookup[playerinput][0]] != 2 ){
                                    if (position[1] + i*lookup[playerinput][0] != 0 && position[0] + i*lookup[playerinput][1] != 0 && position[1] + i*lookup[playerinput][0] != maze.result_width -1 && position[0] + i*lookup[playerinput][1] != maze.result_height -1 ) {
                                        is_writing = true;
                                        this_thread::sleep_for(chrono::milliseconds(50));
                                        printAt( 2*(position[1] + i*lookup[playerinput][0]), position[0] + i*lookup[playerinput][1], effect[playerinput]); // change the moved space 
                                        
                                        printAt( 2*(position[1] + i*lookup[playerinput][0]), position[0] + i*lookup[playerinput][1], maze.glyphs[1]); // change the moved space 
                                        maze.editMap(position[0] + i*lookup[playerinput][1], position[1] + i*lookup[playerinput][0], 1); // edit the map
                                        is_writing = false;
                                        
                                    }
                                    else if (position[1] + i*lookup[playerinput][0] == 0 || position[0] + i*lookup[playerinput][1] == 0 || position[1] + i*lookup[playerinput][0] == maze.result_width -1 || position[0] + i*lookup[playerinput][1] == maze.result_height -1 ) {
                                        break;
                                    }

                                }
                                else if (position[1] + i*lookup[playerinput][0] == 0 || position[0] + i*lookup[playerinput][1] == 0 || position[1] + i*lookup[playerinput][0] == maze.result_width -1 || position[0] + i*lookup[playerinput][1] == maze.result_height -1 ) {
                                    break;
                                }
                            }
                        }
                        else if (playerinput != playerinput2) {
                        for (int i = 1; i <= resolvelist.size(); i++) { //
                            is_writing = true;
                            this_thread::sleep_for(chrono::milliseconds(1));
                            printAt( 2*(position[1] + i*lookup[playerinput2][0]), position[0] + i*lookup[playerinput2][1], maze.glyphs[resolvelist[i-1]]);
                            is_writing = false;
                        }
                        }
                    }
                    break;
                }
                maze.editMap(position[0], position[1], 9);
            }
            else 
                break;
        }
    }
    clearScreen();
    cout << "Maze dimension in chars: " << maze.result_width << "x" << maze.result_height << endl;
    
    return 0;
}

