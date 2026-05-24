#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int rows, cols;

    void dfs(vector<vector<char>>& grid, int i, int j) {
        if (i < 0 || i >= rows || j < 0 || j >= cols || grid[i][j] == '0')
            return;

        grid[i][j] = '0';

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

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == '1') {
                    ++count;
                    dfs(grid, i, j);
                }
            }
        }

        return count;
    }
};

int main() {
    Solution sol;

    // LeetCode Example 1 - single island
    vector<vector<char>> grid1 = {
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'}
    };
    cout << "Test 1: " << sol.numIslands(grid1) << " (Expected: 1)" << endl;

    // LeetCode Example 2 - three islands
    vector<vector<char>> grid2 = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    cout << "Test 2: " << sol.numIslands(grid2) << " (Expected: 3)" << endl;

    // All water
    vector<vector<char>> grid3 = {
        {'0','0','0'},
        {'0','0','0'}
    };
    cout << "Test 3: " << sol.numIslands(grid3) << " (Expected: 0)" << endl;

    // All land
    vector<vector<char>> grid4 = {
        {'1','1'},
        {'1','1'}
    };
    cout << "Test 4: " << sol.numIslands(grid4) << " (Expected: 1)" << endl;

    // Single cell island
    vector<vector<char>> grid5 = {
        {'1'}
    };
    cout << "Test 5: " << sol.numIslands(grid5) << " (Expected: 1)" << endl;

    // Diagonal islands (not connected)
    vector<vector<char>> grid6 = {
        {'1','0','0'},
        {'0','1','0'},
        {'0','0','1'}
    };
    cout << "Test 6: " << sol.numIslands(grid6) << " (Expected: 3)" << endl;

    // Complex pattern
    vector<vector<char>> grid7 = {
        {'1','0','1','0','1'},
        {'0','1','0','1','0'},
        {'1','0','1','0','1'},
        {'0','1','0','1','0'}
    };
    cout << "Test 7: " << sol.numIslands(grid7) << " (Expected: 10)" << endl;

    return 0;
}
