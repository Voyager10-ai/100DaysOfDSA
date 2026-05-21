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

    // LeetCode examples
    vector<int> nums1 = {3, 1, 5, 8};
    cout << "Test 1: " << sol.maxCoins(nums1) << " (Expected: 167)" << endl;

    vector<int> nums2 = {1, 5};
    cout << "Test 2: " << sol.maxCoins(nums2) << " (Expected: 10)" << endl;

    // Edge cases
    vector<int> nums3 = {1};
    cout << "Test 3: " << sol.maxCoins(nums3) << " (Expected: 1)" << endl;

    vector<int> nums4 = {9, 76, 64, 21};
    cout << "Test 4: " << sol.maxCoins(nums4) << " (Expected: 116718)" << endl;

    vector<int> nums5 = {5, 4, 3, 2, 1};
    cout << "Test 5: " << sol.maxCoins(nums5) << " (Expected: 110)" << endl;

    vector<int> nums6 = {2, 3};
    cout << "Test 6: " << sol.maxCoins(nums6) << " (Expected: 12)" << endl;

    vector<int> nums7 = {7, 9, 8, 0, 7, 1, 3, 5, 5, 2};
    cout << "Test 7: " << sol.maxCoins(nums7) << " (Expected: 1717)" << endl;

    return 0;
}
