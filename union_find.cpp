// union_find.cpp
#include "union_find.h"

UnionFind::UnionFind(int n, bool use_pc)
    : parent(n), rank_(n, 1), path_compression(use_pc)
{
    for (int i = 0; i < n; ++i)
        parent[i] = i;
}

int UnionFind::find(int x) {
    sumfind++;
    if (parent[x] == x) return x;
    int root = find(parent[x]);
    if (path_compression)
        parent[x] = root;
    return root;
}

void UnionFind::unite(int rx, int ry) {
    if (rx == ry) return;
    if (rank_[rx] < rank_[ry]) {
        parent[rx] = ry;
        rank_[ry] += rank_[rx];
    } else {
        parent[ry] = rx;
        rank_[rx] += rank_[ry];
    }
}
