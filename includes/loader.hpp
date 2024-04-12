#ifndef LOADER_HPP_
#define LOADER_HPP_

#include <string>
#include <sstream>

using namespace std;

struct State {
    int position[2] = {1, 1}; // row / col
    int** Map2D = nullptr;
    int mapWidth = 0;
    int mapHeight = 0;
    int winCols = 0;
    int winRows = 0;
    string timerPausedTime = "0.0";

    friend ostream& operator<<(ostream& outputFile, const State& gameState) {
        outputFile << gameState.position[0] << " " << gameState.position[1] << endl;
        outputFile << gameState.winCols << " " << gameState.winRows << endl;
        outputFile << gameState.mapHeight << " " << gameState.mapWidth << endl;
        for (int i = 0; i < gameState.mapHeight; i++) {
            for (int j = 0; j < gameState.mapWidth; j++) {
            outputFile << gameState.Map2D[i][j] << " ";
            }
            outputFile << endl;
        }
        outputFile << gameState.timerPausedTime << endl;
        return outputFile;
    }

    State& operator=(const string& fileContents) {
    stringstream ss(fileContents);
    ss >> position[0] >> position[1];
    ss >> winCols >> winRows;
    ss >> mapHeight >> mapWidth;
    Map2D = new int*[mapHeight];
    for (int i = 0; i < mapHeight; i++) {
        Map2D[i] = new int[mapWidth];
        for (int j = 0; j < mapWidth; j++) {
            ss >> Map2D[i][j];
        }
    }
    ss >> timerPausedTime;
    return *this;
}
};

class Loader
{
    string file;

    public:
        State loadState();
        string saveStateToFile(State gameState);
        Loader();
        ~Loader();
};

#endif