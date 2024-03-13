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

    system("clear");

        
    cout << "╔";
    for (int i = 0; i < winCols - 2; i++) 
    {
        cout << "═";
    }
    cout << "╗" << endl;
    
    for (int i = 1; i < winRows - 2; i++) {
        cout << "║" ;
        for (int j = 1; j < winCols - 1; j++){
            cout << " ";
        }
        cout << "║" << endl;
    }

    cout << "╚";
    for (int i = 0; i < winCols - 2; i++) 
    {
        cout << "═";
    }
    cout << "╝" << endl;

    
    
    printAt(1,1, "PLAY");
    printAt(1,2, "QUIT");
    printAt(1,2, COLOR_BG_RED + "QUIT");
    

    char userinput;
    userinput = getch(); //
    if (userinput == 'A' || userinput == 'a') // Userinput "w" instead of "a"?
    {
        printAt(0,1,"PLAY");          // printAt(x-cor, y-cor, std::string)               
        response = 1;
    }
    else if (userinput == 'D' || userinput == 'd') 
    {
        printAt(0,2,"QUIT");
        response = 0;
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