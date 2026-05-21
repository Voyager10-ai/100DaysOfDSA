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

        // Iterate over all possible interval lengths
        for (int len = 2; len < size; ++len) {
            for (int left = 0; left + len < size; ++left) {
                int right = left + len;
                // Try each balloon k as the LAST one to burst in (left, right)
                for (int k = left + 1; k < right; ++k) {
                    int coins = balloons[left] * balloons[k] * balloons[right];
                    coins += dp[left][k] + dp[k][right];
                    dp[left][right] = max(dp[left][right], coins);
                }
            }
        }

        return dp[0][size - 1];
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {3, 1, 5, 8};
    cout << "Test 1: " << sol.maxCoins(nums1) << " (Expected: 167)" << endl;

    vector<int> nums2 = {1, 5};
    cout << "Test 2: " << sol.maxCoins(nums2) << " (Expected: 10)" << endl;

    vector<int> nums3 = {1};
    cout << "Test 3: " << sol.maxCoins(nums3) << " (Expected: 1)" << endl;

    return 0;
}
