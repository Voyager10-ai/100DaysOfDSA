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

// Helper to run a test case
void runTest(int id, vector<vector<int>> edges, vector<int> expected) {
    Solution sol;
    vector<int> result = sol.findRedundantConnection(edges);
    bool pass = (result == expected);
    cout << "Test " << id << ": " << (pass ? "PASS" : "FAIL")
         << " (got [" << result[0] << "," << result[1] << "]"
         << ", expected [" << expected[0] << "," << expected[1] << "])" << endl;
}

int main() {
    // Test 1: LeetCode Example 1 – triangle  1-2-3-1, redundant edge is [1,4]? No:
    //   edges: [1,2],[1,3],[2,3] → answer is [2,3]
    runTest(1, {{1,2},{1,3},{2,3}}, {2,3});

    // Test 2: LeetCode Example 2 – 1-2-3-4-1-5, redundant edge is [1,4]
    runTest(2, {{1,2},{2,3},{3,4},{1,4},{1,5}}, {1,4});

    return 0;
}
