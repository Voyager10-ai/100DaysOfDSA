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

// Helper to run a test case
void runTest(int id, int n, vector<vector<int>> flights, int src, int dst, int k, int expected) {
    Solution sol;
    int result = sol.findCheapestPrice(n, flights, src, dst, k);
    cout << "Test " << id << ": " << (result == expected ? "PASS" : "FAIL")
         << " (got " << result << ", expected " << expected << ")" << endl;
}

int main() {
    // Test 1: LeetCode Example 1 – 4 cities, 1 stop allowed
    runTest(1, 4, {{0,1,100},{1,2,100},{2,0,100},{1,3,600},{2,3,200}}, 0, 3, 1, 700);

    // Test 2: LeetCode Example 2 – same graph, 0 stops → no path with 0 stops
    runTest(2, 4, {{0,1,100},{1,2,100},{2,0,100},{1,3,600},{2,3,200}}, 0, 3, 0, -1);

    // Test 3: Direct flight exists – 0 stops sufficient
    runTest(3, 3, {{0,1,100},{0,2,500},{1,2,100}}, 0, 2, 0, 500);

    // Test 4: Cheaper with 1 stop – 0→1→2 = 200 < direct 500
    runTest(4, 3, {{0,1,100},{0,2,500},{1,2,100}}, 0, 2, 1, 200);

    return 0;
}
