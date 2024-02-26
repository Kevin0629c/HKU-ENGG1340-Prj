#ifndef DISJOINT_HPP_
#define DISJOINT_HPP_

#include <unordered_map>

using namespace std;

class DisjointSet
{
private:
    unordered_map<int, int> parent;
    unordered_map<int, int> rank;

public:
    void make_set(int v);
    int find(int v);
    void union_sets(int a, int b);
};

#endif