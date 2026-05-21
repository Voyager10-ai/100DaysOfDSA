#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();

        // Add virtual balloons with value 1 at both ends
        vector<int> balloons(n + 2, 1);
        for (int i = 0; i < n; ++i) {
            balloons[i + 1] = nums[i];
        }

        int size = n + 2;
        // dp[i][j] = max coins from bursting all balloons between i and j (exclusive)
        vector<vector<int>> dp(size, vector<int>(size, 0));

        return dp[0][size - 1];
    }
};
