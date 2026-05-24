#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int rows, cols;

    void dfs(vector<vector<char>>& grid, int i, int j) {
        // DFS helper to sink the island
    }

    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;

        rows = grid.size();
        cols = grid[0].size();
        int count = 0;

        return count;
    }
};
