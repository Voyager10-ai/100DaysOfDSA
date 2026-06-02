#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    // Bellman-Ford variant limited to K+1 relaxation rounds
    // flights[i] = [from, to, price]
    // Returns cheapest price from src to dst with at most k stops, or -1 if unreachable
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // dist[i] = cheapest cost to reach node i from src
        vector<int> dist(n, INT_MAX);
        dist[src] = 0;

        // Relax all edges up to k+1 times (k stops = k+1 edges)
        for (int i = 0; i <= k; ++i) {
            // Copy current distances to avoid using updates from this round
            vector<int> temp(dist);

            for (auto& f : flights) {
                int u = f[0], v = f[1], w = f[2];
                if (dist[u] != INT_MAX && dist[u] + w < temp[v]) {
                    temp[v] = dist[u] + w;
                }
            }

            dist = temp;
        }

        return dist[dst] == INT_MAX ? -1 : dist[dst];
    }
};
