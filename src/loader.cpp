#include "loader.hpp"
#include "helpers.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

Loader::Loader() {
}

Loader::~Loader() {
    // Destructor
}

State Loader::loadState() {
    int winCols = getWinCols();
    int winRows = getWinRows();
    frame(winCols, winRows);
    
    string m1 = "Please enter the file name in 'states/'";
    string m2 = "[                                   ]";
    printAt(winCols/2 - m1.length()/2, winRows/2 - 1, m1);
    printAt(winCols/2 - m2.length()/2, winRows/2, m2);
    cursorShow();
    toggleEcho();
    moveCursorTo(winCols/2 - m2.length()/2 + 1, winRows/2);
    cin >> file;
    toggleEcho();
    cursorHide();


    // loadedState: load the state from file contents
    string filePath = "../states/" + file;
    ifstream inputFile(filePath);
    if (inputFile.is_open()) {
        stringstream buffer; // https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
        buffer << inputFile.rdbuf();
        loadedState = buffer.str();
    } else {
        cout << "Unable to open file. " << file << endl;
    }
}

void Loader::saveStateToFile(State gameState) {
    string filePath = "../states/game_state";
    ofstream outputFile(filePath);
    if (outputFile.is_open()) {
        outputFile << gameState;
        outputFile.close();
        cout << "Game state saved to file: " << filePath << endl;
    } else {
        cout << "Unable to open file: " << filePath << endl;
    }
}