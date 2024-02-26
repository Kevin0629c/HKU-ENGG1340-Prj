#include "gameflow.hpp"
// #include "helpers.hpp"
// #include "termcolor.hpp"
#include "disjoint.hpp"

#include <iostream>
#include <vector>
#include <random>
#include <unordered_map>
#include <algorithm>

using namespace std;

/* ----------- Constructor ---------- */
Gameflow::Gameflow(int theWidth, int theHeight, int theSeed)
{
    width = theWidth;
    height = theHeight;
    seed = theSeed;
    map2D = new int *[theWidth];

    for (int i = 0; i < theWidth; ++i)
    {
        map2D[i] = new int[theHeight];
        for (int j = 0; j < theHeight; ++j)
        {
            map2D[i][j] = theWidth * i + j;
        }
    }

    kruskalize();
}

void Gameflow::kruskalize()
{
    // edge = ((row1, col1), (row2, col2)) such that grid[row][col] = key
    vector<pair<pair<int, int>, pair<int, int>>> edges_ordered;

    // First add all neighboring edges into a list
    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            pair<int, int> cell = make_pair(col, row);
            pair<int, int> left_cell = make_pair(col - 1, row);
            pair<int, int> down_cell = make_pair(col, row - 1);
            vector<pair<pair<int, int>, pair<int, int>>> near;

            // if not a boundary cell, add edge, else ignore
            if (col > 0)
            {
                near.push_back(make_pair(left_cell, cell));
            }
            if (row > 0)
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
    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            // the key is the cells unique id
            int key = map2D[col][row];
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

    int key_count = map2D[width - 1][height - 1]; // last key
    while (edge_count < key_count)
    {
        // get next edge ((row1, col1), (row2,col2))
        auto edge = edges.back();
        edges.pop_back();
        // get the sets for each vertex in the edge
        int key_a = map2D[edge.first.first][edge.first.second];
        int key_b = map2D[edge.second.first][edge.second.second];
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
}

/* ------------ Functions ----------- */
void Gameflow::printGame()
{
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            cout << map2D[i][j] << " ";
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
    }
    delete[] map2D;
}