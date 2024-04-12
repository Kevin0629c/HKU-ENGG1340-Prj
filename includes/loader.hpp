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
    int timerPausedTime = 0;

    friend ostream& operator<<(ostream& outputFile, const State& gameState) {
        outputFile << gameState.position[0] << " " << gameState.position[1] << endl;
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

    void operator=(string fileContents) {
        stringstream ss(fileContents);
        ss >> position[0] >> position[1];
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                ss >> Map2D[i][j];
            }
        }
        ss >> timerPausedTime;
    }
};

class Loader
{
    string file;

    public:
        State loadedState;
        State loadState();
        void saveStateToFile(State gameState);
        Loader();
        ~Loader();
};

#endif