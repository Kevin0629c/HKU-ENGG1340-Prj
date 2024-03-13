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
    // Add this line to specify the namespace for "cout"

    //int size_w = 60 , size_h = 20;
    //int selected = 1;            //input value dont know what is this
    //int option_count = 5;             //(just for sub sth misssing dont use this as last result)
    //int title_pos = (option_count == 0) ? size_h * 0.5 - 1 : size_h * 0.35;
    //string title = "Hello";            //list(menu_data.keys())[0] how to do this 

    frame(winCols,winRows);
    
    printAt(1,1, COLOR_BG_RED + "PLAY");
    printAt(1,2, "QUIT");
    

    char userinput ;
    userinput = getch();
    while (userinput != 'D'&& userinput != 'd')
    {   
        userinput = getch();
        printAt(1,1,COLOR_DEFAULT + "PLAY");
        printAt(1,2,COLOR_DEFAULT + "QUIT");
        if (userinput == 'W' || userinput == 'w') 
        {
            printAt(1,1,COLOR_BG_RED + "PLAY");          // printAt(x-cor, y-cor, std::string)               
            response = 0;
        }
        else if (userinput == 'S' || userinput == 's') 
        {
            printAt(1,2,COLOR_BG_RED + "QUIT");
            response = -1;
        }
        
    }

    return response;
}

/*     Main menu structure fyr:
|- Play
|- Gamemodes
|  |- Classic 
|  |- Squares 
|- Options** 
|  |- Color customization
|- Quit
*/