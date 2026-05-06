/*
 * Problem: Longest Increasing Subsequence
 * Day: 70
 * 
 * Description:
 * Given an integer array nums, return the length of the longest strictly increasing subsequence.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Longest Increasing Subsequence using Dynamic Programming
    // Time Complexity: O(N^2)
    // Space Complexity: O(N)
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        int n = nums.size();
        vector<int> dp(n, 1);
        int max_len = 1;
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            max_len = max(max_len, dp[i]);
        }
        
        return max_len;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1
    vector<int> nums1 = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "Input: nums = [10, 9, 2, 5, 3, 7, 101, 18]\nOutput: " << sol.lengthOfLIS(nums1) << "\nExpected: 4\n\n";
    
    // Test Case 2
    vector<int> nums2 = {0, 1, 0, 3, 2, 3};
    cout << "Input: nums = [0, 1, 0, 3, 2, 3]\nOutput: " << sol.lengthOfLIS(nums2) << "\nExpected: 4\n\n";

    // Test Case 3
    vector<int> nums3 = {7, 7, 7, 7, 7, 7, 7};
    cout << "Input: nums = [7, 7, 7, 7, 7, 7, 7]\nOutput: " << sol.lengthOfLIS(nums3) << "\nExpected: 1\n\n";

    return 0;
}
