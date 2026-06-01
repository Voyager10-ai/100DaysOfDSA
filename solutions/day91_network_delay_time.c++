#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Solution {
public:
    // Dijkstra's algorithm – find the minimum time for all nodes to receive the signal
    // times[i] = [u, v, w] means edge from u to v with weight w
    // n = number of nodes (1-indexed), k = source node
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // Build adjacency list: node → [(neighbor, weight)]
        vector<vector<pair<int,int>>> adj(n + 1);
        for (auto& t : times)
            adj[t[0]].push_back({t[1], t[2]});

        // Dijkstra with min-heap: (distance, node)
        vector<int> dist(n + 1, INT_MAX);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
        dist[k] = 0;
        pq.push({0, k});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            // Skip stale entries
            if (d > dist[u]) continue;

            for (auto& [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        // The answer is the maximum shortest distance across all nodes
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (dist[i] == INT_MAX) return -1; // unreachable node
            ans = max(ans, dist[i]);
        }
        return ans;
    }
};

// Helper to run a test case
void runTest(int id, vector<vector<int>> times, int n, int k, int expected) {
    Solution sol;
    int result = sol.networkDelayTime(times, n, k);
    cout << "Test " << id << ": " << (result == expected ? "PASS" : "FAIL")
         << " (got " << result << ", expected " << expected << ")" << endl;
}

int main() {
    // Test 1: LeetCode Example 1 – 4 nodes, source 2, answer 2
    runTest(1, {{2,1,1},{2,3,1},{3,4,1}}, 4, 2, 2);

    // Test 2: LeetCode Example 2 – single node, no edges
    runTest(2, {}, 1, 1, 0);

    // Test 3: LeetCode Example 3 – 2 nodes, unreachable node 2
    runTest(3, {{1,2,1}}, 2, 2, -1);

    // Test 4: Diamond DAG – two paths, shorter wins
    //   1→2 (w=1), 1→3 (w=4), 2→3 (w=2), 2→4 (w=6), 3→4 (w=1)
    //   Shortest to 4: 1→2→3→4 = 1+2+1 = 4
    runTest(4, {{1,2,1},{1,3,4},{2,3,2},{2,4,6},{3,4,1}}, 4, 1, 4);

    // Test 5: Fully connected 3 nodes – all edges weight 1, source 1
    //   max dist = 1 (all reachable in 1 step)
    runTest(5, {{1,2,1},{1,3,1},{2,1,1},{2,3,1},{3,1,1},{3,2,1}}, 3, 1, 1);

    // Test 6: Linear chain 1→2→3→4→5, each weight 10 → max = 40
    runTest(6, {{1,2,10},{2,3,10},{3,4,10},{4,5,10}}, 5, 1, 40);

    // Test 7: Parallel edges – multiple edges between same nodes, shorter one wins
    //   1→2 (w=5), 1→2 (w=2) → should use w=2
    runTest(7, {{1,2,5},{1,2,2}}, 2, 1, 2);

    // Test 8: Star graph – source 1 to all others, varying weights
    //   1→2(3), 1→3(7), 1→4(1), 1→5(9) → max = 9
    runTest(8, {{1,2,3},{1,3,7},{1,4,1},{1,5,9}}, 5, 1, 9);

    // Test 9: Disconnected graph – node 3 unreachable from source 1
    runTest(9, {{1,2,1},{2,1,1}}, 3, 1, -1);

    // Test 10: Large chain stress test (500 nodes)
    {
        int n = 500;
        vector<vector<int>> t;
        for (int i = 1; i < n; ++i)
            t.push_back({i, i + 1, 1});
        runTest(10, t, n, 1, n - 1);
    }

    return 0;
}
