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
    int response = 0;
    int winCols = getWinCols();
    int winRows = getWinRows();

    using namespace std;
    string top = R"(╭──────╮)";
    string mid = R"(│      │)";
    string bot = R"(╰──────╯)";

    string play = R"(PLAY)";

    string quit = R"(QUIT)";

    frame(winCols,winRows);
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
x                                                        )");

    botton(winCols-29,(winRows/2)-5,COLOR_GREEN, play);

    botton(winCols-29,(winRows/2)+2,COLOR_DEFAULT,quit);

    

    char userinput ;
    userinput = getch();

    while (userinput != 'D'&& userinput != 'd')
    {

        botton(winCols-29,(winRows/2)-5,COLOR_DEFAULT, play);
        botton(winCols-29,(winRows/2)+2,COLOR_DEFAULT,quit);
        if (userinput == 'W' || userinput == 'w') 
        {
            botton(winCols-29,(winRows/2)-5,COLOR_GREEN, play);          // printAt(x-cor, y-cor, std::string)               
            response = 0;
        }
        else if (userinput == 'S' || userinput == 's') 
        {
            botton(winCols-29,(winRows/2)+2,COLOR_RED,quit);
            response = -1;
        }
        userinput = getch();
    }

    return response;
}

