#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int rows, cols;

    void dfs(vector<vector<char>>& grid, int i, int j) {
        // Boundary check and water check
        if (i < 0 || i >= rows || j < 0 || j >= cols || grid[i][j] == '0')
            return;

        // Sink the land to mark as visited
        grid[i][j] = '0';

        // Explore all 4 directions
        dfs(grid, i + 1, j);
        dfs(grid, i - 1, j);
        dfs(grid, i, j + 1);
        dfs(grid, i, j - 1);
    }

    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;

        rows = grid.size();
        cols = grid[0].size();
        int count = 0;

        return count;
    }
};
