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
