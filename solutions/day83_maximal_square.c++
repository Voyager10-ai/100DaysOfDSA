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

        // dp[i][j] = side length of largest square with bottom-right at (i,j)
        vector<vector<int>> dp(rows, vector<int>(cols, 0));

        return maxSide * maxSide;
    }
};
