#include <iostream>
#include <vector>

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

int main() {
    return 0;
}

