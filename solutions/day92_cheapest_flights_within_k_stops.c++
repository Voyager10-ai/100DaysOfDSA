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
    }
};
