#include "maze2D.hpp"
#include "disjoint.hpp"
#include "colors.hpp"

#include <iostream>
#include <vector>
#include <random>
#include <unordered_map>
#include <algorithm>
#include <sstream>

using namespace std;


/* ----------- Constructor ---------- */
Maze2D::Maze2D(int theWidth, int theHeight, int theSeed)
{
    width = theWidth / 2;
    height = theHeight / 2;
    seed = theSeed;
    result_width = theWidth + 1;
    result_height = theHeight;

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
    
    map2D = new int*[result_height];
    for (int i = 0; i < result_height; i++) {
        map2D[i] = new int[result_width];
    }

    glyphs = {
        {9, COLOR_BLUE + "██" + COLOR_DEFAULT},                    // player
        {8, COLOR_BLACK + "██" + COLOR_DEFAULT},                   // tail
        {1, "  "},                                                 // space
        {0, "██"},                                                 // wall
        {2, COLOR_YELLOW + "⟋⟋" + COLOR_DEFAULT},                  // end
        {3, COLOR_BG_MAGENTA + COLOR_WHITE + "❂❂" + COLOR_DEFAULT} // portal
    };

    kruskalize();
    generateMaze();
    
}

/* -------------- Utils ------------- */
void Maze2D::printMap()
{
    for (int r = 0; r < result_height; ++r)
    {
        for (int c = 0; c < result_width; ++c)
        {
            cout << glyphs[map2D[r][c]];
            // cout << map2D[r][c];
        }
        cout << endl;
    }
}

void Maze2D::editMap(int r, int c, int value)
{
    map2D[r][c] = value;
}

void Maze2D::printTransfers()
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
Maze2D::~Maze2D()
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

void Maze2D::generateMaze()
{
    /*
    To translate generated "transfers" into a 2D array, 
    we loop through grid2D and transfers, then create 2 rows 
    based on the data in those variables per iteration of the loop.
    */
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

    /*
    Then we assign random end points as well as
    minigame portals to the 2D array.
    */

    random_device rd; 
    mt19937 g(rd()); // g is a random number generator, not a random number

    int exit_col, exit_row;
    while (true) {
        exit_col = g() % (width / 2 + 1) + width / 2; // generate numbers
        exit_row = g() % (height ) + 1;
            if (g() % 2 + 1 == 1) { // flip a coin to decide if the exit should be at the bottom or right edge
                if (map2D[exit_row][result_width - 2] == 1) { // checks if the position is a valid exit position
                    map2D[exit_row][result_width - 1] = 2; 
                    break;
                } else if (map2D[result_height - 2][exit_col] == 1) {
                    map2D[result_height - 1][exit_col] = 2; 
                    break;
                }
            }
        }

   int portal_edge_margin = 2;
   float portal_rate = 0.4;

   vector<pair<int, int> > portal_candidates;
    for (int r = portal_edge_margin; r < result_height - portal_edge_margin; ++r) {
        for (int c = portal_edge_margin; c < result_width - portal_edge_margin; ++c) {
            int checking = map2D[r][c];
            if (checking == 1) {
                int wall_count = 0;
                vector<int> neighbors = {map2D[r][c+1], map2D[r][c-1], map2D[r+1][c], map2D[r-1][c]};
                for (int v : neighbors) {
                    if (v == 0) {
                        ++wall_count;
                    }
                }
                if (wall_count >= 3) {
                    portal_candidates.push_back(make_pair(r, c));
                    // cout << r << " " << c << endl;
                }
            }
        }
    }

    int num_portals = static_cast<int>(portal_candidates.size() * portal_rate);

    // Note: shuffle takes a random number generator as a third argument
    shuffle(portal_candidates.begin(), portal_candidates.end(), g); // shuffle the candidates
    vector<pair<int, int> > portals(portal_candidates.begin(), portal_candidates.begin() + num_portals); // first n elements of the candidiates

    for (auto pos : portals) {
        map2D[pos.first][pos.second] = 3;
    }
   

}

void Maze2D::kruskalize()
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
}