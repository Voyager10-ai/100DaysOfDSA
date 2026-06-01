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
    }
};
