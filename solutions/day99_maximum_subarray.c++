#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// LeetCode 53 – Maximum Subarray
//
// Given an integer array nums, find the subarray with the largest sum, and return its sum.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Constraints:
//   1 <= nums.length <= 10^5
//   -10^4 <= nums[i] <= 10^4
//
// Examples:
//   Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
//   Output: 6
//   Explanation: The subarray [4,-1,2,1] has the largest sum 6.
//
//   Input: nums = [1]
//   Output: 1
//
//   Input: nums = [5,4,-1,7,8]
//   Output: 23


// Brute-force approach: Check all subarrays
// For every starting index i, extend the subarray to every ending index j >= i,
// keeping a running sum and tracking the maximum.
// Time Complexity: O(N^2) where N is nums.size().
// Space Complexity: O(1)
class SolutionAlt {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        int maxSum = INT_MIN;

        for (int i = 0; i < n; ++i) {
            int currentSum = 0;
            for (int j = i; j < n; ++j) {
                currentSum += nums[j];
                maxSum = max(maxSum, currentSum);
            }
        }

        return maxSum;
    }
};


// Optimal approach: Kadane's Algorithm (Dynamic Programming)
// At each index, decide whether to extend the previous subarray or start fresh.
// current_sum = max(nums[i], current_sum + nums[i])
// Track the global maximum across all positions.
// Time Complexity: O(N) where N is nums.size().
// Space Complexity: O(1)
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxSum = nums[0];
        int currentSum = nums[0];

        for (int i = 1; i < (int)nums.size(); ++i) {
            // Either extend the existing subarray or start a new one at i
            currentSum = max(nums[i], currentSum + nums[i]);
            maxSum = max(maxSum, currentSum);
        }

        return maxSum;
    }
};


int testNum = 0;
void check(int gotOpt, int gotAlt, int expected, const string& desc) {
    ++testNum;
    bool passOpt = (gotOpt == expected);
    bool passAlt = (gotAlt == expected);
    bool pass = passOpt && passAlt;

    cout << "Test " << testNum << ": " << (pass ? "PASS" : "FAIL")
         << " - " << desc << endl;
    if (!passOpt) {
        cout << "  -> Optimal failed: got " << gotOpt << ", expected " << expected << endl;
    }
    if (!passAlt) {
        cout << "  -> Alt failed: got " << gotAlt << ", expected " << expected << endl;
    }
}

int main() {
    Solution solver;
    SolutionAlt solverAlt;

    // Test 1: LeetCode Example 1
    {
        vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
        check(solver.maxSubArray(nums), solverAlt.maxSubArray(nums), 6, "Example 1: nums=[-2,1,-3,4,-1,2,1,-5,4]");
    }

    // Test 2: LeetCode Example 2 – single element
    {
        vector<int> nums = {1};
        check(solver.maxSubArray(nums), solverAlt.maxSubArray(nums), 1, "Example 2: nums=[1]");
    }

    // Test 3: LeetCode Example 3 – all positive
    {
        vector<int> nums = {5, 4, -1, 7, 8};
        check(solver.maxSubArray(nums), solverAlt.maxSubArray(nums), 23, "Example 3: nums=[5,4,-1,7,8]");
    }

    // Test 4: All negative numbers
    {
        vector<int> nums = {-3, -5, -1, -7};
        check(solver.maxSubArray(nums), solverAlt.maxSubArray(nums), -1, "All negatives: nums=[-3,-5,-1,-7]");
    }

    // Test 5: All positive numbers – entire array is the answer
    {
        vector<int> nums = {1, 2, 3, 4};
        check(solver.maxSubArray(nums), solverAlt.maxSubArray(nums), 10, "All positives: nums=[1,2,3,4]");
    }

    // Test 6: Single negative element
    {
        vector<int> nums = {-1};
        check(solver.maxSubArray(nums), solverAlt.maxSubArray(nums), -1, "Single negative: nums=[-1]");
    }

    // Test 7: Alternating positive and negative
    {
        vector<int> nums = {2, -1, 2, -1, 2};
        check(solver.maxSubArray(nums), solverAlt.maxSubArray(nums), 4, "Alternating: nums=[2,-1,2,-1,2]");
    }

    // Test 8: Large negatives surrounding a positive cluster
    {
        vector<int> nums = {-100, 3, 5, -2, 8, -100};
        check(solver.maxSubArray(nums), solverAlt.maxSubArray(nums), 14, "Bookended negatives: nums=[-100,3,5,-2,8,-100]");
    }

    return 0;
}
