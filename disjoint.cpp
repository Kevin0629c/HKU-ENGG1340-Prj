#include "disjoint.hpp"

#include <unordered_map>

using namespace std;

void DisjointSet::make_set(int v)
{
    parent[v] = v;
    rank[v] = 0;
}

int DisjointSet::find(int v)
{
    if (v == parent[v])
    {
        return v;
    }
    // Path compression
    return parent[v] = find(parent[v]);
}

void DisjointSet::union_sets(int a, int b)
{
    a = find(a);
    b = find(b);
    if (a != b)
    {
        // Union by rank
        if (rank[a] < rank[b])
        {
            swap(a, b);
        }
        parent[b] = a;
        if (rank[a] == rank[b])
        {
            ++rank[a];
        }
    }
}