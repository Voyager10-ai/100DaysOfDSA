#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// LeetCode 1192 – Critical Connections in a Network
// Given n servers (0 to n-1) and undirected connections, find all critical
// connections (bridges) whose removal disconnects the graph.
// Uses Tarjan's Bridge-Finding Algorithm.

class Solution {
    int timer = 0;
    vector<vector<int>> adj;      // adjacency list
    vector<int> disc;             // discovery time of each node
    vector<int> low;              // lowest disc reachable from subtree
    vector<vector<int>> bridges;  // result: all critical connections

    // DFS to find bridges
    // u     = current node
    // parent = node we came from (to avoid traversing the same edge back)
    void dfs(int u, int parent) {
        disc[u] = low[u] = timer++;

        for (int v : adj[u]) {
            if (v == parent) continue;  // skip the edge back to parent

            if (disc[v] == -1) {
                // Tree edge — recurse
                dfs(v, u);

                // After returning, update low[u] from child
                low[u] = min(low[u], low[v]);

                // Bridge condition: no back-edge from v's subtree reaches u or above
                if (low[v] > disc[u]) {
                    bridges.push_back({u, v});
                }
            } else {
                // Back edge — update low[u]
                low[u] = min(low[u], disc[v]);
            }
        }
    }

public:
    // Finds all bridges (critical connections) in the undirected graph
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        timer = 0;
        adj.assign(n, {});
        disc.assign(n, -1);
        low.assign(n, -1);
        bridges.clear();

        // Build adjacency list
        for (auto& e : connections) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        // Run DFS from node 0 (graph is guaranteed connected)
        dfs(0, -1);

        return bridges;
    }
};

// Normalize edges for comparison: sort each edge, then sort the list
vector<vector<int>> normalize(vector<vector<int>> edges) {
    for (auto& e : edges) sort(e.begin(), e.end());
    sort(edges.begin(), edges.end());
    return edges;
}

// Helper to run a test case
void runTest(int id, int n, vector<vector<int>> connections,
             vector<vector<int>> expected) {
    Solution sol;
    auto result = sol.criticalConnections(n, connections);

    auto normResult   = normalize(result);
    auto normExpected  = normalize(expected);

    bool pass = (normResult == normExpected);
    cout << "Test " << id << ": " << (pass ? "PASS" : "FAIL") << endl;
    if (!pass) {
        cout << "  Expected: {";
        for (auto& e : normExpected) cout << "[" << e[0] << "," << e[1] << "] ";
        cout << "}" << endl;
        cout << "  Got:      {";
        for (auto& e : normResult) cout << "[" << e[0] << "," << e[1] << "] ";
        cout << "}" << endl;
    }
}

int main() {
    // Test 1: LeetCode Example – one bridge between node 1 and 3
    runTest(1, 4, {{0,1},{1,2},{2,0},{1,3}}, {{1,3}});

    // Test 2: Simple chain 0–1–2 — both edges are bridges
    runTest(2, 3, {{0,1},{1,2}}, {{0,1},{1,2}});

    // Test 3: Triangle — no bridges (every edge is in a cycle)
    runTest(3, 3, {{0,1},{1,2},{2,0}}, {});

    // Test 4: Two triangles connected by a bridge (2–3)
    // 0-1-2  and  3-4-5  with bridge 2–3
    runTest(4, 6, {{0,1},{1,2},{2,0},{2,3},{3,4},{4,5},{5,3}}, {{2,3}});

    // Test 5: Star graph – every edge is a bridge
    // Center node 0 connected to 1, 2, 3, 4
    runTest(5, 5, {{0,1},{0,2},{0,3},{0,4}}, {{0,1},{0,2},{0,3},{0,4}});

    // Test 6: Complete graph K4 – no bridges
    runTest(6, 4, {{0,1},{0,2},{0,3},{1,2},{1,3},{2,3}}, {});

    // Test 7: Linear chain 0–1–2–3–4 – all 4 edges are bridges
    runTest(7, 5, {{0,1},{1,2},{2,3},{3,4}},
            {{0,1},{1,2},{2,3},{3,4}});

    // Test 8: Two nodes, single edge – that edge is a bridge
    runTest(8, 2, {{0,1}}, {{0,1}});

    // Test 9: Cycle with a tail – 0-1-2-0 with tail 2–3
    // Bridge is 2–3
    runTest(9, 4, {{0,1},{1,2},{2,0},{2,3}}, {{2,3}});

    // Test 10: Multiple bridges in a barbell graph
    // Cycle 0-1-2-0, bridge 2–3, chain 3–4, cycle 4-5-6-4
    runTest(10, 7, {{0,1},{1,2},{2,0},{2,3},{3,4},{4,5},{5,6},{6,4}},
            {{2,3},{3,4}});

    // Test 11: Figure-eight – two cycles sharing node 2, no bridges
    runTest(11, 5, {{0,1},{1,2},{2,0},{2,3},{3,4},{4,2}}, {});

    // Test 12: Larger test – diamond with pendant
    // Diamond: 0-1, 0-2, 1-3, 2-3 (no bridges), pendant: 3-4 (bridge)
    runTest(12, 5, {{0,1},{0,2},{1,3},{2,3},{3,4}}, {{3,4}});

    return 0;
}

