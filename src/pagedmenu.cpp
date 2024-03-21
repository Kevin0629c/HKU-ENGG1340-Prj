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

    
    printAt(winCols-30,3, COLOR_BG_RED + play);
    printAt(winCols-30,11, quit);
    

    char userinput ;
    userinput = getch();
    while (userinput != 'D'&& userinput != 'd')
    {           
        printAt(winCols-30,3,COLOR_DEFAULT + play);
        printAt(winCols-30,11,COLOR_DEFAULT + quit);
        if (userinput == 'W' || userinput == 'w') 
        {
            printAt(winCols-30,3,COLOR_BG_RED + play);          // printAt(x-cor, y-cor, std::string)               
            response = 0;
        }
        else if (userinput == 'S' || userinput == 's') 
        {
            printAt(winCols-30,11,COLOR_BG_RED + quit);
            response = -1;
        }
        userinput = getch();
    }

    return response;
}

