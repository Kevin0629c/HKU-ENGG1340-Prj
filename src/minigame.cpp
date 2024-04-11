#include "minigame.hpp"
#include "helpers.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <thread>
#include <chrono>

using namespace std;

Minigame::Minigame()
{
}

Minigame::~Minigame()
{
}

/* ▲ ▼ ◀ ▶ */

bool Minigame::countdown(int winCols, int winRows) {

        int duration=15;
        string bar_symbol = "■ ";

        string line = "0 : 0 : 00";
        int mid_col = (winCols-line.size())/2;
        int mid_col1 = (winCols-29)/2;

        for (int i = 0; i <= 15; i++) {

                if (i<=5) {
                        string timer = "0 : 0 : " + to_string(duration-i);
                        printAt(mid_col, 2, timer);

                        string bar;
                        for (int j=0;j<duration-i;j++) {
                                bar+=bar_symbol;
                        }
                        printAt(mid_col1, 1, bar);
                        
                        this_thread::sleep_for(chrono::seconds(1));
                        printAt(mid_col1, 1, "                               ");
                } else if (i>5) {
                        string timer = "0 : 0 : 0" + to_string(duration-i);
                        printAt(mid_col, 2, timer);

                        string bar;
                        for (int j=0;j<duration-i;j++) {
                                bar+=bar_symbol;
                        }
                        printAt(mid_col1, 1, bar);

                        this_thread::sleep_for(chrono::seconds(1));
                        printAt(mid_col1, 1, "                               ");
                }
                if (i==15) {
                        string quote =  "Oops! Time's out";
                        int mid_col2 = (winCols-quote.size())/2;
                        printAt(mid_col2, 1, quote);

                        this_thread::sleep_for(chrono::seconds(1));
                        return false;  
                } 

                if (stopCountdown) {
                        return false;
                }
        }
        return false;
} 

bool Minigame::direction() {
        char answer[10];
        int arr[10];

        int col = getWinCols();
        int row = getWinRows();

        int midcol = (col-68)/2;
        int midrow = (row-5)/2;


        string arrows[4] = {"▲", "▼", "◀", "▶"};
        srand(time(NULL));
        for (int i = 0; i < 10; i++) {
                int number = rand() % 4;
                arr[i] = number;
        };

        string quote = "Enter the corresponding arrow (wasd)";
        int midcol1 = (col-quote.size())/2;
        printAt(midcol1, midrow+4, quote);

        printAt(midcol, midrow, "╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮");
        printAt(midcol, midrow+1, "│ " + arrows[arr[0]] + " │  │ " + arrows[arr[1]] + " │  │ " + arrows[arr[2]] + " │  │ " + arrows[arr[3]] + " │  │ " + arrows[arr[4]] + " │  │ " + arrows[arr[5]] + " │  │ " + arrows[arr[6]] + " │  │ " + arrows[arr[7]] + " │  │ " + arrows[arr[8]] + " │  │ " + arrows[arr[9]] + " │");
        printAt(midcol, midrow+2, "╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯");

/* ▲ ▼ ◀ ▶ */
        for (int i = 0; i < 10; ++i) {

                char letter1 = 'w'; 
                char letter2 = 's'; 
                char letter3 = 'a'; 
                char letter4 = 'd'; 

        if ( arrows[arr[i]] == "▲") {
                answer[i] = letter1;
        } else if ( arrows[arr[i]] == "▼" ) {
                answer[i] = letter2;
        } else if ( arrows[arr[i]] == "◀" ) {
                answer[i] = letter3;
        } else if ( arrows[arr[i]] == "▶" ) {
                answer[i] = letter4;
        } else {
                printAt(3, 3, "wrong");
        }
        }        
                
        string output[10] ={arrows[arr[0]], arrows[arr[1]], arrows[arr[2]], arrows[arr[3]], arrows[arr[4]], arrows[arr[5]], arrows[arr[6]], arrows[arr[7]], arrows[arr[8]], arrows[arr[9]]};

        for (int i = 0; i < 10; i++) {
                char input = getch();
                if (input != answer[i]) {
                        string quote="         Oops! Wrong input :(         ";
                        int mid_col1 = (col-quote.size())/2;
                        printAt(mid_col1,midrow+4,quote);
                        return false;
                } else if (input == answer[i]) {
                        output[i] = "✔";
                        printAt(midcol, midrow, "╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮");
                        printAt(midcol, midrow+1, "│ " + output[0] + " │  │ " + output[1] + " │  │ " + output[2] + " │  │ " + output[3] + " │  │ " + output[4] + " │  │ " + output[5] + " │  │ " + output[6] + " │  │ " + output[7] + " │  │ " + output[8] + " │  │ " + output[9] + " │");
                        printAt(midcol, midrow+2, "╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯");
                        if (output[9]=="✔") 
                                return true;
                }
        }   

}

bool Minigame::run()
{
        int winCols = getWinCols();
        int winRows = getWinRows();
 
        frame(winCols, winRows); 

        string quote = "Press any key to start";
        int mid_col = (winCols-quote.size())/2;
        int mid_row = (winRows-1)/2;
        printAt(mid_col, mid_row,quote);
        char c = getch();
        printAt(mid_col, mid_row, "                      ");

        bool countdown_result=true;
        thread countdown_thread([&]() {
                countdown_result=countdown(winCols, winRows);
        });

        bool result;
        result = direction();

        if (result) {
                int midrow = (winRows-5)/2;
                string quote1 = "            Wohoooo nice!            ";
                int mid_col1 = (winCols-quote1.size())/2;
                printAt(mid_col1,midrow+4,quote1);
                return 1;
        } else if (countdown_result==false || result==false) {
                return 0;
        } 

        countdown_thread.join();
        return 0;
}
