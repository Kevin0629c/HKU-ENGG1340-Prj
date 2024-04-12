#include "loader.hpp"
#include "helpers.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

Loader::Loader()
{
}

Loader::~Loader()
{
    // Destructor
}

State Loader::loadState()
{
    State loadedState;

    string filePath = "../states/game_state";
    ifstream inputFile(filePath);
    if (inputFile.is_open())
    {
        stringstream buffer; // https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
        buffer << inputFile.rdbuf();
        loadedState = buffer.str();
    }
    else
    {
        string m = "There are no saved states. Try saving a game by hitting P in-game.";

        int winCols = getWinCols();
        int winRows = getWinRows();
        frame(winCols, winRows);

        printAt(winCols / 2 - m.length() / 2, winRows / 2, m);
        getch();
    }
    return loadedState;
}

string Loader::saveStateToFile(State gameState)
{
    string filePath = "../states/game_state";
    ofstream outputFile(filePath);
    if (outputFile.is_open())
    {
        outputFile << gameState;
        outputFile.close();
        cout << "Game state saved to file: " << filePath << endl;
    }
    else
    {
        cout << "ERROR: Unable to save file. " << filePath << endl;
        exit(0);
    }
    return filePath;
}