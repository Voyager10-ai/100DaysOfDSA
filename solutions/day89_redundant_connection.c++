#include <iostream>
#include <vector>

using namespace std;

class UnionFind {
public:
    vector<int> parent, rank_;

    UnionFind(int n) : parent(n + 1), rank_(n + 1, 0) {
        for (int i = 0; i <= n; ++i)
            parent[i] = i;
    }

    // Path-compressed find
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    // Union by rank – returns false if already connected (cycle detected)
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;

        if (rank_[px] < rank_[py]) swap(px, py);
        parent[py] = px;
        if (rank_[px] == rank_[py]) ++rank_[px];
        return true;
    }
};
