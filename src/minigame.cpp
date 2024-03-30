#include "minigame.hpp"
#include "helpers.hpp"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <thread>
#include <chrono>

using namespace std;

int count = 0;

Minigame::Minigame()
{
}

Minigame::~Minigame()
{
}

/* ▲ ▼ ◀ ▶ */

void Minigame::countdown(int x, int y) {

        int timer = 15;

        for (int i = 0; i < 15; i++) {
                string timer = "0 : 0 : " + to_string(timer-i);
                printAt(x, y, timer);
                this_thread::sleep_for(chrono::seconds(1));
                clearScreen();                                           //Exit the scene
        }

        if (timer == 0) {
                exit(0);
                return 1;
        }

} 

void Minigame::bar(int &pos) {
    string empty(10 - pos, '\u25AF');
    string process(pos, '\u2592');
    printAt(winCols - 29, (winRows / 2) + 10, empty);
    printAt(winCols - 29 + 10 * pos, (winRows / 2) + 10, process);
    clearScreen();
}


bool Minigame::direction() {
        int pos = 0;
        char answer[10];
        int arr[10];

        int col = getWinCols();
        int row = getWinRows();

        int midCol = col/2;       // Clarification required (CODE NOT USED)
        int midRow = row/2;       // Clarification required (CODE NOT USED)

        string arrows[4] = {"▲", "▼", "◀", "▶"};
        srand(time(NULL));
        for (int i = 0; i < 10; i++) {
                int number = rand() % 4;
                arr[i] = number;
        };

        printAt(2, 2, "Enter the corresponding arrow (wasd)");

        printAt(20, 10, "╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮");
        printAt(20, 11, "│ " + arrows[arr[0]] + " │  │ " + arrows[arr[1]] + " │  │ " + arrows[arr[2]] + " │  │ " + arrows[arr[3]] + " │  │ " + arrows[arr[4]] + " │  │ " + arrows[arr[5]] + " │  │ " + arrows[arr[6]] + " │  │ " + arrows[arr[7]] + " │  │ " + arrows[arr[8]] + " │  │ " + arrows[arr[9]] + " │");
        printAt(20, 12, "╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯");

/* ▲ ▼ ◀ ▶ */
        for (int i = 0; i < 10; ++i) {

                char letter1 = 'w'; 
                char letter2 = 's'; 
                char letter3 = 'a'; 
                char letter4 = 'd'; 

        if ( arrows[arr[i]] == "▲") {
                answer[i] = letter1;
                pos += 1;
        } else if ( arrows[arr[i]] == "▼" ) {
                answer[i] = letter2;
                pos += 1;
        } else if ( arrows[arr[i]] == "◀" ) {
                answer[i] = letter3;
                pos += 1;
        } else if ( arrows[arr[i]] == "▶" ) {
                answer[i] = letter4;
                pos += 1;
        } else {
                printAt(3, 3, "wrong");
        }
        }        

        printAt(20, 13, "____________________________________________________________________");
                
        string output[10] ={arrows[arr[0]], arrows[arr[1]], arrows[arr[2]], arrows[arr[3]], arrows[arr[4]], arrows[arr[5]], arrows[arr[6]], arrows[arr[7]], arrows[arr[8]], arrows[arr[9]]};

        for (int i = 0; i < 10; i++) {
                char input = getch();
                if (input != answer[i]) {
                        printAt(10, 5, "Oops");
                        return 0;
                } else if (input == answer[i]) {
                        output[i] = "✔";
                        printAt(20, 10, "╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮");
                        printAt(20, 11, "│ " + output[0] + " │  │ " + output[1] + " │  │ " + output[2] + " │  │ " + output[3] + " │  │ " + output[4] + " │  │ " + output[5] + " │  │ " + output[6] + " │  │ " + output[7] + " │  │ " + output[8] + " │  │ " + output[9] + " │");
                        printAt(20, 12, "╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯");
                        if (output[9]=="✔") 
                                return 1;
                }
        }   

}

/*void check() {
        for (int i = 0; i < 5; ++i) {
                char input;
                cin >> input;
                if (input != arr[i])
                        return false;
        
        }
        return true
} */


/*╭──────╮
  │      │
  ╰──────╯*/

int Minigame::run()
{
        int winCols = getWinCols();
        int winRows = getWinRows();

        frame(winCols, winRows); 

        printAt(5, 5, "Press any key to start");
        char c = getch();
        printAt(5, 5, "                      ");

        thread countdown_thread([&]() {
                countdown(40, 0);
        });

        int pos = 0;

        if (direction()) {
            printAt(47, 15, "Yeahhhh");
            exit(0);
        } else {
                count++;
                bar(pos);                     // Call the bar function passing pos as a reference
                printAt(2, 3, "Chances left : "+ to_string(4-count));
                run();

                if (count==4) {
                        exit(0);             // you fail
                        return 1;
                }
        }

        countdown_thread.join();

        return 0;
}

/*(✓, ✔,✓     for (int i = 0; i < 10; ++i) {
                char input = getch();
                if (input != answer[i]) {
                        printAt(10, 5, "Oops");
                        return 1;
                } else if (input == answer[i]) {
                        printAt(20, 10, "╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮  ╭───╮");
                        printAt(20, 11, "│ " + "✔" + " │  │ " + arrows[arr[1]] + " │  │ " + arrows[arr[2]] + " │  │ " + arrows[arr[3]] + " │  │ " + arrows[arr[4]] + " │  │ " + arrows[arr[5]] + " │  │ " + arrows[arr[6]] + " │  │ " + arrows[arr[7]] + " │  │ " + arrows[arr[8]] + " │  │ " + arrows[arr[9]] + " │");
                        printAt(20, 12, "╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯  ╰───╯");
                        continue;
                }
        }
        return 0;
        
} */

/*void check() {
        for (int i = 0; i < 5; ++i) {
                char input;
                cin >> input;
                if (input != arr[i])
                 return false;
        
        }
        return true
} */


/*╭──────╮
  │      │
  ╰──────╯

int Minigame::run()
{
        int winCols = getWinCols();
        int winRows = getWinRows();

        frame(winCols, winRows); 

        printAt(5, 5, "Press any key to start");
        char c = getch();
        printAt(5, 5, "                      ");

        if (direction() == false) {
                printAt(10, 5, "     ");
                exit(0);
        } 

        return 0;
}

(✓, ✔,✓*/