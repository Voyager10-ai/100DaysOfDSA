#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;

        int rows = matrix.size();
        int cols = matrix[0].size();
        int maxSide = 0;

        vector<vector<int>> dp(rows, vector<int>(cols, 0));

        // Base cases: first row and first column
        for (int i = 0; i < rows; ++i) {
            dp[i][0] = matrix[i][0] - '0';
            maxSide = max(maxSide, dp[i][0]);
        }
        for (int j = 0; j < cols; ++j) {
            dp[0][j] = matrix[0][j] - '0';
            maxSide = max(maxSide, dp[0][j]);
        }

        // DP transition: min of top, left, top-left neighbors + 1
        for (int i = 1; i < rows; ++i) {
            for (int j = 1; j < cols; ++j) {
                if (matrix[i][j] == '1') {
                    dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                    maxSide = max(maxSide, dp[i][j]);
                }
            }
        }

        return maxSide * maxSide;
    }
};

int main() {
    Solution sol;

    // LeetCode Example 1
    vector<vector<char>> matrix1 = {
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    };
    cout << "Test 1: " << sol.maximalSquare(matrix1) << " (Expected: 4)" << endl;

    // LeetCode Example 2
    vector<vector<char>> matrix2 = {
        {'0','1'},
        {'1','0'}
    };
    cout << "Test 2: " << sol.maximalSquare(matrix2) << " (Expected: 1)" << endl;

    // All zeros
    vector<vector<char>> matrix3 = {
        {'0'}
    };
    cout << "Test 3: " << sol.maximalSquare(matrix3) << " (Expected: 0)" << endl;

    // Single '1'
    vector<vector<char>> matrix4 = {
        {'1'}
    };
    cout << "Test 4: " << sol.maximalSquare(matrix4) << " (Expected: 1)" << endl;

    // Entire matrix of 1s
    vector<vector<char>> matrix5 = {
        {'1','1','1'},
        {'1','1','1'},
        {'1','1','1'}
    };
    cout << "Test 5: " << sol.maximalSquare(matrix5) << " (Expected: 9)" << endl;

    // Large square embedded
    vector<vector<char>> matrix6 = {
        {'0','0','0','0','0'},
        {'0','1','1','1','0'},
        {'0','1','1','1','0'},
        {'0','1','1','1','0'},
        {'0','0','0','0','0'}
    };
    cout << "Test 6: " << sol.maximalSquare(matrix6) << " (Expected: 9)" << endl;

    // Single row
    vector<vector<char>> matrix7 = {
        {'1','1','0','1','1','1'}
    };
    cout << "Test 7: " << sol.maximalSquare(matrix7) << " (Expected: 1)" << endl;

    // Single column
    vector<vector<char>> matrix8 = {
        {'1'},
        {'1'},
        {'0'},
        {'1'}
    };
    cout << "Test 8: " << sol.maximalSquare(matrix8) << " (Expected: 1)" << endl;

    return 0;
}
