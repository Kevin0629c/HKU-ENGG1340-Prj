#include "gameflow.hpp"
// #include "helpers.hpp"
// #include "termcolor.hpp"
#include "disjoint.hpp"
#include "colors.hpp"

#include <iostream>
#include <vector>
#include <random>
#include <unordered_map>
#include <algorithm>
#include <unordered_map>
#include <sstream>

using namespace std;

/* ----------- Constructor ---------- */
Gameflow::Gameflow(int theWidth, int theHeight, int theSeed)
{
    width = theWidth;
    height = theHeight;
    seed = theSeed;

    // create the 2D array for the MST algorithm
    grid2D = new int *[theWidth / 2];
    for (int i = 0; i < theWidth / 2; ++i)
    {
        grid2D[i] = new int[theHeight / 2];
        for (int j = 0; j < theHeight / 2; ++j)
        {
            grid2D[i][j] = theWidth / 2 * i + j;
        }
    }
    glyphs = {
        {9, COLOR_BLUE + "██" + COLOR_DEFAULT},                    // player
        {8, COLOR_BLACK + "██" + COLOR_DEFAULT},                   // tail
        {1, "  "},                                                 // space
        {0, "██"},                                                 // wall
        {2, COLOR_YELLOW + "⟋⟋" + COLOR_DEFAULT},                  // end
        {3, COLOR_MAGENTA + COLOR_BG_WHITE + "❂❂" + COLOR_DEFAULT} // portal
    };

    // for (int i = 0; i < width /2; ++i)
    // {
    //     for (int j = 0; j < height /2; ++j)
    //     {
    //         cout << grid2D[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    

    kruskalize();
    printTransfers();
    generateMaze();
    printGame();
    
}

/* -------------- Utils ------------- */
void Gameflow::printGame()
{
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            // cout << glyphs[map2D[i][j]];
            cout << map2D[i][j];
        }
        cout << endl;
    }
}

void Gameflow::printTransfers()
{
    for (auto const &x : transfers)
    {
        cout << x.first << ": ";
        for (auto const &y : x.second)
        {
            cout << y.first << " ";
        }
        cout << endl;
    }
}

/* ----------- Destructor ----------- */
Gameflow::~Gameflow()
{
    for (int i = 0; i < width; ++i)
    {
        delete[] map2D[i];
        delete[] grid2D[i];
    }
    delete[] map2D;
    delete[] grid2D;
}

/* ----------- Generators ----------- */

void Gameflow::generateMaze()
{
    const int h = height + 1;
    const int w = width + 1;
    map2D = new int*[h];
    for (int i = 0; i < h; ++i) {
        map2D[i] = new int[w];
    }

    for (int row = 1; row < height / 2; ++row) {
        // vector<int> buildRow;

        // buildRow.push_back(0);
        // if (row == 1) {
        //     buildRow.push_back(9);
        // } else {
        //     buildRow.push_back(1);
        // }

        // for (int col = 1; col < width / 2; ++col) {
        //     if (transfers[grid2D[row][col]].find(grid2D[row][col-1]) != transfers[grid2D[row][col]].end()) {
        //         buildRow.push_back(1);
        //     } else {
        //         buildRow.push_back(0);
        //     }
        //     buildRow.push_back(1);
        // }
        // buildRow.push_back(0);
        
        // for (int i = 0; i < buildRow.size(); ++i) {
        //     map2D[row][i] = buildRow[i];
        // }

    //     for (int col = 0; col < width; ++col) {
    //         map2D[row*2+2][col*2] = 0;
    //         int key = grid2D[col][row];
    //         if (row+1 < height && transfers[key].find(grid2D[col][row+1]) != transfers[key].end()) {
    //             map2D[row*2+2][col*2+1] = 1;
    //         } else {
    //             map2D[row*2+2][col*2+1] = 0;
    //         }
    //     }
    //     map2D[row*2+2][width*2] = 0;
    }
}

void Gameflow::kruskalize()
{
    // // edge = ((row1, col1), (row2, col2)) such that grid[row][col] = key
    // vector<pair<pair<int, int>, pair<int, int>>> edges_ordered;

    // // First add all neighboring edges into a list
    // for (int row = 0; row < height / 2; ++row)
    // {
    //     for (int col = 0; col < width / 2; ++col)
    //     {
    //         pair<int, int> cell = make_pair(col, row);
    //         pair<int, int> left_cell = make_pair(col - 1, row);
    //         pair<int, int> down_cell = make_pair(col, row - 1);
    //         vector<pair<pair<int, int>, pair<int, int>>> near;

    //         // if not a boundary cell, add edge, else ignore
    //         if (col > 0)
    //         {
    //             near.push_back(make_pair(left_cell, cell));
    //         }
    //         if (row > 0)
    //         {
    //             near.push_back(make_pair(down_cell, cell));
    //         }
    //         edges_ordered.insert(edges_ordered.end(), near.begin(), near.end());
    //     }
    // }

    // // seed the random value
    // srand(seed);
    // vector<pair<pair<int, int>, pair<int, int>>> edges;

    // // shuffle the ordered edges randomly into a new list
    // while (!edges_ordered.empty())
    // {
    //     // randomly pop an edge
    //     int index = rand() % edges_ordered.size();
    //     edges.push_back(edges_ordered[index]);
    //     edges_ordered.erase(edges_ordered.begin() + index);
    // }

    // DisjointSet disjoint_set;
    // for (int row = 0; row < height / 2; ++row)
    // {
    //     for (int col = 0; col < width / 2; ++col)
    //     {
    //         // the key is the cells unique id
    //         int key = grid2D[col][row];
    //         // create the singleton
    //         disjoint_set.make_set(key);
    //         // initialize the keys transfer dict
    //         transfers[key] = unordered_map<int, bool>();
    //     }
    // }

    // int edge_count = 0;
    // // eulers formula e = v-1, so the
    // // minimum required edges is v for a connected graph!
    // // each cell is identified by its key, and each key is a vertex on the MST

    // int key_count = grid2D[width / 2 - 1][height / 2 - 1]; // last key
    // while (edge_count < key_count)
    // {
    //     // get next edge ((row1, col1), (row2,col2))
    //     auto edge = edges.back();
    //     edges.pop_back();
    //     // get the sets for each vertex in the edge
    //     int key_a = grid2D[edge.first.first][edge.first.second];
    //     int key_b = grid2D[edge.second.first][edge.second.second];
    //     int set_a = disjoint_set.find(key_a);
    //     int set_b = disjoint_set.find(key_b);
    //     // if they are not in the same set they are not in the
    //     // same region in the maze
    //     if (set_a != set_b)
    //     {
    //         // add the transfer between the cells,
    //         // graph is undirected and will search
    //         // [a][b] or [b][a]
    //         edge_count++;
    //         transfers[key_a][key_b] = true;
    //         transfers[key_b][key_a] = true;
    //         disjoint_set.union_sets(set_a, set_b);
    //     }
    // }

    transfers = {
    {0, { {1, true}, {5, true} }},
    {1, { {0, true} }},
    {2, { {3, true} }},
    {3, { {8, true}, {2, true}, {4, true} }},
    {4, { {9, true}, {3, true} }},
    {5, { {10, true}, {0, true} }},
    {6, { {11, true}, {7, true} }},
    {7, { {8, true}, {6, true}, {12, true} }},
    {8, { {7, true}, {3, true} }},
    {9, { {4, true}, {14, true} }},
    {10, { {15, true}, {11, true}, {5, true} }},
    {11, { {6, true}, {16, true}, {10, true} }},
    {12, { {7, true}, {13, true} }},
    {13, { {12, true} }},
    {14, { {19, true}, {9, true} }},
    {15, { {10, true}, {20, true} }},
    {16, { {11, true}, {21, true} }},
    {17, { {18, true} }},
    {18, { {19, true}, {17, true} }},
    {19, { {14, true}, {18, true}, {24, true} }},
    {20, { {15, true} }},
    {21, { {16, true} }},
    {22, { {23, true} }},
    {23, { {22, true}, {24, true} }},
    {24, { {19, true}, {23, true} }}
};
}