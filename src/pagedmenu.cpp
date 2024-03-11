#include "pagedmenu.hpp"
#include "helpers.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

PagedMenu::PagedMenu(char theMenu_data)
{
    menu_data = theMenu_data;
}

PagedMenu::~PagedMenu()
{
}

int PagedMenu::displayMenu()
{
    int response = 0;
    int winCols = getWinCols();
    int winRows = getWinRows();

    cout << "╔";
    for (int i = 0; i < winCols - 2; i++)
    {
        cout << "═";
    }
    cout << "╗" << endl;

    for (int i = 1; i < winRows - 2; i++) {
        cout << "║";
        for (int j = 1; j < winCols - 2; j++) {
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

    
    
    

            
    
    

    return response;
}