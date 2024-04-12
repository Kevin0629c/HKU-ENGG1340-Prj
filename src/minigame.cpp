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

bool Minigame::countdown(int col, int row) { // countdown timer with a bar shown //

        int duration=10;
        string bar_symbol = "■ ";

        string line = "0 : 0 : 00";             
        int midcol_timer = (col-line.size())/2; // allow the string to be placed in the middle //
        int midcol_bar = (col-19)/2;

        for (int i = 0; i <= 10; i++) { 

                if (i==0) {                                                     
                        string timer = "0 : 0 : " + to_string(duration-i);      // written two conditions to avoid errors when //
                        printAt(midcol_timer, 2, timer);                        // there is only one digit remaining in the time value. //
                                                                                // e.g. if the remaining time= 9, //
                        string bar;                                             // it will not print out the wrong value such as 90. //
                        for (int j=0;j<duration-i;j++) {
                                bar+=bar_symbol;
                        }
                        printAt(midcol_bar, 1, bar);
                        
                        this_thread::sleep_for(chrono::seconds(1));
                        printAt(midcol_bar, 1, "                               ");
                } else if (i>=1) {
                        string timer = "0 : 0 : 0" + to_string(duration-i);
                        printAt(midcol_timer, 2, timer);

                        string bar;
                        for (int j=0;j<duration-i;j++) {
                                bar+=bar_symbol;
                        }
                        printAt(midcol_bar, 1, bar);

                        this_thread::sleep_for(chrono::seconds(1));
                        printAt(midcol_bar, 1, "                               ");
                }
                if (i==10) {                                    // if time's out, user loses the game // 
                        string quote =  "Oops! Time's out";
                        int midcol_quote = (col-quote.size())/2;
                        printAt(midcol_quote, 1, quote);

                        this_thread::sleep_for(chrono::seconds(1));
                        return false;  
                } 

                if (stopCountdown) { // if user input the wrong input, the timer stops //
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

        string arrows[4] = {"▲", "▼", "◀", "▶"}; // randomly generate the output //
        srand(time(NULL));
        for (int i = 0; i < 10; i++) {
                int number = rand() % 4;
                arr[i] = number;
        };

        string quote = "Enter the corresponding arrow (wasd)";
        int midcol_quote = (col-quote.size())/2;
        printAt(midcol_quote, midrow+4, quote);

        printAt(midcol, midrow, "╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮");
        printAt(midcol, midrow+1, "│ " + arrows[arr[0]] + " │  │ " + arrows[arr[1]] + " │  │ " + arrows[arr[2]] + " │  │ " + arrows[arr[3]] + " │  │ " + arrows[arr[4]] + " │  │ " + arrows[arr[5]] + " │  │ " + arrows[arr[6]] + " │  │ " + arrows[arr[7]] + " │  │ " + arrows[arr[8]] + " │  │ " + arrows[arr[9]] + " │");
        printAt(midcol, midrow+2, "╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯");

        for (int i = 0; i < 10; ++i) { // turn the output into an answer list //

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

        for (int i = 0; i < 10; i++) {          // check user's answer one by one //
                char input = getch();
                if (input != answer[i]) {                                       // if user's input is wrong //
                        string quote="         Oops! Wrong input :(         ";
                        this_thread::sleep_for(chrono::seconds(1));
                        int midcol_quote = (col-quote.size())/2;
                        printAt(midcol_quote,midrow+4,quote);
                        return false;
                } else if (input == answer[i]) {                                // if user's input is correct //
                        output[i] = "✔";
                        printAt(midcol, midrow, "╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮");
                        printAt(midcol, midrow+1, "│ " + output[0] + " │  │ " + output[1] + " │  │ " + output[2] + " │  │ " + output[3] + " │  │ " + output[4] + " │  │ " + output[5] + " │  │ " + output[6] + " │  │ " + output[7] + " │  │ " + output[8] + " │  │ " + output[9] + " │");
                        printAt(midcol, midrow+2, "╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯");
                        if (output[9]=="✔")                                    // if the last answer is correct == all correct //
                                return true;
                }
        }   

}

bool Minigame::run()
{
        int winCols = getWinCols();
        int winRows = getWinRows();
 
        frame(winCols, winRows); 

        string quote = "Press any key to start";        // start screen //
        int mid_col = (winCols-quote.size())/2;
        int mid_row = (winRows-1)/2;
        printAt(mid_col, mid_row,quote);

        char c = getch();
        printAt(mid_col, mid_row, "                      ");

        bool countdown_result=true;                             // allow countdown function and the game run at the same time using thread //
        thread countdown_thread([&]() {
                countdown_result=countdown(winCols, winRows);
        });

        bool result;
        result = direction();

        if (result) {                                                   // win situation //
                int midrow = (winRows-5)/2;
                string quote = "            Wohoooo nice!            ";
                this_thread::sleep_for(chrono::seconds(1));
                int midcol_quote = (winCols-quote.size())/2;
                printAt(midcol_quote,midrow+4,quote);
                return 1;

        } else if (countdown_result==false || result==false) {          // lose situation //
                return 0;
        } 

        countdown_thread.join();
        return 0;
}
