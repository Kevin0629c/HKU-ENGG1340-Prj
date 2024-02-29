#include "pagedmenu.hpp"
#include "helpers.hpp"

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
    return response;
}