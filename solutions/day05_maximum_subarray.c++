#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // Kadane's Algorithm - O(n) time, O(1) space
    int maxSubArray(vector<int>& nums) {
        int maxSum = nums[0];
        int currentSum = nums[0];
        
        for (int i = 1; i < nums.size(); i++) {
            // Either extend the current subarray or start a new one
            currentSum = max(nums[i], currentSum + nums[i]);
            maxSum = max(maxSum, currentSum);
        }
        
        return maxSum;
    }
};
