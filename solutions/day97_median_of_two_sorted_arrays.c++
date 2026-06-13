#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <climits>

using namespace std;

// LeetCode 4 – Median of Two Sorted Arrays
// Given two sorted arrays nums1 and nums2 of size m and n respectively,
// return the median of the two sorted arrays.
//
// The overall run time complexity should be O(log (m+n)).
//
// Example 1:
//   Input: nums1 = [1,3], nums2 = [2]
//   Output: 2.00000
//   Explanation: merged array = [1,2,3] and median is 2.
//
// Example 2:
//   Input: nums1 = [1,2], nums2 = [3,4]
//   Output: 2.50000
//   Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.

// Alternative approach: Merge two sorted arrays
// Time: O(m + n), Space: O(m + n)
class SolutionAlt {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        vector<int> merged;
        merged.reserve(m + n);
        
        int i = 0, j = 0;
        while (i < m && j < n) {
            if (nums1[i] <= nums2[j]) {
                merged.push_back(nums1[i++]);
            } else {
                merged.push_back(nums2[j++]);
            }
        }
        while (i < m) merged.push_back(nums1[i++]);
        while (j < n) merged.push_back(nums2[j++]);
        
        int total = m + n;
        if (total % 2 == 1) {
            return merged[total / 2];
        } else {
            return (merged[total / 2 - 1] + merged[total / 2]) / 2.0;
        }
    }
};

// Optimal approach: Binary Search on the smaller array
// Time: O(log(min(m, n))), Space: O(1)
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // Ensure nums1 is the smaller array to do binary search on.
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }
        
        int m = nums1.size();
        int n = nums2.size();
        
        int lo = 0;
        int hi = m;
        int half_len = (m + n + 1) / 2;
        
        while (lo <= hi) {
            int i = lo + (hi - lo) / 2;
            int j = half_len - i;
            
            int left1 = (i == 0) ? INT_MIN : nums1[i - 1];
            int right1 = (i == m) ? INT_MAX : nums1[i];
            
            int left2 = (j == 0) ? INT_MIN : nums2[j - 1];
            int right2 = (j == n) ? INT_MAX : nums2[j];
            
            if (left1 <= right2 && left2 <= right1) {
                // Perfect partition found
                if ((m + n) % 2 == 1) {
                    return max(left1, left2);
                } else {
                    return (max(left1, left2) + min(right1, right2)) / 2.0;
                }
            } else if (left1 > right2) {
                // i is too big, move left
                hi = i - 1;
            } else {
                // i is too small, move right
                lo = i + 1;
            }
        }
        
        return 0.0;
    }
};

