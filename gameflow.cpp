#include "gameflow.hpp"
// #include "helpers.hpp"
// #include "termcor.hpp"
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
    width = theWidth / 2;
    height = theHeight / 2;
    seed = theSeed;

    // create the 2D array for the MST algorithm
   grid2D = new int*[height];
    for (int i = 0; i < height; i++) {
        grid2D[i] = new int[width];
    }

    // Initialize the array
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            grid2D[i][j] = width * i + j;
        }
    }
    
    map2D = new int*[height * 2 + 1];
    for (int i = 0; i < height * 2 + 1; i++) {
        map2D[i] = new int[width * 2 + 1];
    }

    glyphs = {
        {9, COLOR_BLUE + "██" + COLOR_DEFAULT},                    // player
        {8, COLOR_BLACK + "██" + COLOR_DEFAULT},                   // tail
        {1, "  "},                                                 // space
        {0, "██"},                                                 // wall
        {2, COLOR_YELLOW + "⟋⟋" + COLOR_DEFAULT},                  // end
        {3, COLOR_MAGENTA + COLOR_BG_WHITE + "❂❂" + COLOR_DEFAULT} // portal
    };

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout << grid2D[i][j] << " ";
        }
        std::cout << std::endl;
    }

    kruskalize();
    printTransfers();
    generateMaze();
    printGame();
    
}

/* -------------- Utils ------------- */
void Gameflow::printGame()
{
    for (int r = 0; r < height * 2 + 1; ++r)
    {
        for (int c = 0; c < width * 2 + 1; ++c)
        {
            cout << glyphs[map2D[r][c]];
            // cout << map2D[r][c];
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
    for (int c = 0; c < height; ++c)
    {
        delete[] map2D[c];
        delete[] grid2D[c];
    }
    delete[] map2D;
    delete[] grid2D;
}

/* ----------- Generators ----------- */

void Gameflow::generateMaze()
{
    int bC, bR;
    bR = 0;

    for (int r = 0; r < height; ++r) {
        ++bR;
        bC = 0;

        map2D[bR][bC] = 0;
        ++bC;
        if (r == 0) {
            map2D[bR][bC] = 9;
        } else {
            map2D[bR][bC] = 1;
        }
        ++bC;

        for (int c = 1; c < width; ++c) {
            if (transfers[grid2D[r][c]].find(grid2D[r][c-1]) != transfers[grid2D[r][c]].end()) {
                map2D[bR][bC] = 1;
            } else {
                map2D[bR][bC] = 0;
            }
            ++bC;
           map2D[bR][bC] = 1;
            ++bC;
        }
        map2D[bR][bC] = 0;

        ++bR;
        bC = 0;

        for (int c = 0; c < width; ++c) {
            map2D[bR][bC] = 0;
            ++bC;
            int key = grid2D[r][c];
            if (r+1 < height && transfers[key].find(grid2D[r+1][c]) != transfers[key].end()) {
                map2D[bR][bC] = 1;
            } else {
                map2D[bR][bC] = 0;
            }
            ++bC;
        }
        map2D[bR][bC] = 0;
    }
}

void Gameflow::kruskalize()
{
    // edge = ((r1, c1), (r2, c2)) such that grid[r][c] = key
    vector<pair<pair<int, int>, pair<int, int>>> edges_ordered;

    // First add all neighboring edges into a list
    for (int r = 0; r < height; ++r)
    {
        for (int c = 0; c < width; ++c)
        {
            pair<int, int> cell = make_pair(c, r);
            pair<int, int> left_cell = make_pair(c - 1, r);
            pair<int, int> down_cell = make_pair(c, r - 1);
            vector<pair<pair<int, int>, pair<int, int>>> near;

            // if not a boundary cell, add edge, else ignore
            if (c > 0)
            {
                near.push_back(make_pair(left_cell, cell));
            }
            if (r > 0)
            {
                near.push_back(make_pair(down_cell, cell));
            }
            edges_ordered.insert(edges_ordered.end(), near.begin(), near.end());
        }
    }

    // seed the random value
    srand(seed);
    vector<pair<pair<int, int>, pair<int, int>>> edges;

    // shuffle the ordered edges randomly into a new list
    while (!edges_ordered.empty())
    {
        // randomly pop an edge
        int index = rand() % edges_ordered.size();
        edges.push_back(edges_ordered[index]);
        edges_ordered.erase(edges_ordered.begin() + index);
    }

    DisjointSet disjoint_set;
    for (int r = 0; r < height; ++r)
    {
        for (int c = 0; c < width; ++c)
        {
            // the key is the cells unique id
            int key = grid2D[r][c];
            // create the singleton
            disjoint_set.make_set(key);
            // initialize the keys transfer dict
            transfers[key] = unordered_map<int, bool>();
        }
    }

    int edge_count = 0;
    // eulers formula e = v-1, so the
    // minimum required edges is v for a connected graph!
    // each cell is identified by its key, and each key is a vertex on the MST

    int key_count = grid2D[height - 1][width - 1]; // last key
    while (edge_count < key_count)
    {
        // get next edge ((r1, c1), (r2,c2))
        auto edge = edges.back();
        edges.pop_back();
        // get the sets for each vertex in the edge
        int key_a = grid2D[edge.first.second][edge.first.first];
        int key_b = grid2D[edge.second.second][edge.second.first];
        int set_a = disjoint_set.find(key_a);
        int set_b = disjoint_set.find(key_b);
        // if they are not in the same set they are not in the
        // same region in the maze
        if (set_a != set_b)
        {
            // add the transfer between the cells,
            // graph is undirected and will search
            // [a][b] or [b][a]
            edge_count++;
            transfers[key_a][key_b] = true;
            transfers[key_b][key_a] = true;
            disjoint_set.union_sets(set_a, set_b);
        }
    }

    // transfers = {
    // {0, { {1, true}, {5, true} }},
    // {1, { {0, true} }},
    // {2, { {3, true} }},
    // {3, { {8, true}, {2, true}, {4, true} }},
    // {4, { {9, true}, {3, true} }},
    // {5, { {10, true}, {0, true} }},
    // {6, { {11, true}, {7, true} }},
    // {7, { {8, true}, {6, true}, {12, true} }},
    // {8, { {7, true}, {3, true} }},
    // {9, { {4, true}, {14, true} }},
    // {10, { {15, true}, {11, true}, {5, true} }},
    // {11, { {6, true}, {16, true}, {10, true} }},
    // {12, { {7, true}, {13, true} }},
    // {13, { {12, true} }},
    // {14, { {19, true}, {9, true} }},
    // {15, { {10, true}, {20, true} }},
    // {16, { {11, true}, {21, true} }},
    // {17, { {18, true} }},
    // {18, { {19, true}, {17, true} }},
    // {19, { {14, true}, {18, true}, {24, true} }},
    // {20, { {15, true} }},
    // {21, { {16, true} }},
    // {22, { {23, true} }},
    // {23, { {22, true}, {24, true} }},
    // {24, { {19, true}, {23, true} }}
// };
}