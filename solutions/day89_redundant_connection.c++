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

class Solution {
public:
    // Return the last edge that, when added, creates a cycle
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        UnionFind uf(n);

        for (auto& e : edges) {
            // If union fails, both nodes are already connected → cycle
            if (!uf.unite(e[0], e[1]))
                return e;
        }

        return {}; // unreachable per problem constraints
    }
};
