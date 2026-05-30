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

    // Test 3: Simple pair – two nodes, one redundant edge
    //   edges: [1,2],[1,2] → second [1,2] is redundant
    runTest(3, {{1,2},{1,2}}, {1,2});

    // Test 4: Linear chain closed into a cycle at the end
    //   1-2-3-4-5-1 → last edge [5,1] creates cycle
    runTest(4, {{1,2},{2,3},{3,4},{4,5},{5,1}}, {5,1});

    // Test 5: Star graph – center node 1 connected to 2,3,4,5 then 2-3 closes cycle
    runTest(5, {{1,2},{1,3},{1,4},{1,5},{2,3}}, {2,3});

    // Test 6: Square cycle – 1-2-3-4-1, redundant edge is [4,1]
    runTest(6, {{1,2},{2,3},{3,4},{4,1}}, {4,1});

    // Test 7: Multiple possible redundant edges – last one in input wins
    //   Triangle 1-2-3-1 plus edge 3-4 plus closing edge 2-4
    runTest(7, {{1,2},{2,3},{3,1},{3,4},{2,4}}, {2,4});

    // Test 8: Large chain stress test (1000 nodes, closing edge at end)
    {
        int n = 1000;
        vector<vector<int>> edges;
        for (int i = 1; i < n; ++i)
            edges.push_back({i, i + 1});
        edges.push_back({n, 1}); // closes the cycle
        runTest(8, edges, {n, 1});
    }

    return 0;
}
