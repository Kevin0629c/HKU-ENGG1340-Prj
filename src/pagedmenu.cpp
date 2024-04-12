#include "pagedmenu.hpp"
#include "helpers.hpp"
#include "colors.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

PagedMenu::PagedMenu()
{
}

PagedMenu::~PagedMenu()
{
}

int PagedMenu::displayMenu()
{
    int response = 0;                                                                   // response is defulted to 0 (Play)
    int winCols = getWinCols();                                                         // console width
    int winRows = getWinRows();                                                         // console height

    using namespace std;
    string top = R"(╭──────╮)";
    string mid = R"(│      │)";
    string bot = R"(╰──────╯)";

    string play = R"(PLAY)";                                                            // the pattern of play

    string quit = R"(QUIT)";                                                            // the pattern of quit

    frame(winCols,winRows);                                                             // the UI frame
    printAt(1,(winRows/2)-5,R"(         
x        _    __  __    _     ________ _   _  ____    
x       / \  |  \/  |  / \   |__  /_ _| \ | |/ ___|   
x      / _ \ | |\/| | / _ \    / / | ||  \| | |  _    
x     / ___ \| |  | |/ ___ \  / /_ | || |\  | |_| |   
x    /_/__ \_\_|  |_/_/   \_\/____|___|_| \_|\____|__ 
x    | __ )|  _ \| ____|  / \  | |/ / _ \| | | |_   _|
x    |  _ \| |_) |  _|   / _ \ | ' / | | | | | | | |  
x    | |_) |  _ <| |___ / ___ \| . \ |_| | |_| | | |  
x    |____/|_| \_\_____/_/   \_\_|\_\___/ \___/  |_|  
x                                                           )");                        // the title showed in UI

    botton(winCols-29,(winRows/2)-5,COLOR_GREEN, play);                                // botton is a function in helers.cpp which helps 
                                                                                       // building a thin frame around the words
    botton(winCols-29,(winRows/2)+2,COLOR_DEFAULT,quit);                               // botton(x_coor of the word, y_coor of the word, colour , word to be showed)

    

    char userinput ;                                                                    // detect user input
    userinput = getch();                                                                

    while (userinput != 'D'&& userinput != 'd')                                         // D is the botton for confriming the choice
    {

        botton(winCols-29,(winRows/2)-5,COLOR_DEFAULT, play);                           // changes colour when playing moving their choices
        botton(winCols-29,(winRows/2)+2,COLOR_DEFAULT,quit);
        if (userinput == 'W' || userinput == 'w')                                       // the play botton is on the top so "W" is used to move to the top 
        {
            botton(winCols-29,(winRows/2)-5,COLOR_GREEN, play);                         // the botton of "PLAY" changes to green when player moves the choice to that
            response = 0;                                                               // response = 0 = play
        }
        else if (userinput == 'S' || userinput == 's')                                  // the quit botton is at the bottom so "S" is used 
        {
            botton(winCols-29,(winRows/2)+2,COLOR_RED,quit);
            response = -1;                                                              // response = -1 = quit
        }
        userinput = getch();                                                            // getting the next userinput
    }

    return response;                                                                    // outputing the choice of player
}

