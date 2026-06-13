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
//
// Algorithm:
//   1. To find the median, we partition both arrays into left and right halves.
//      Total elements in the left half = (m + n + 1) / 2.
//   2. We perform binary search on the smaller array (nums1) to find partition index `i`.
//      Consequently, the partition index in nums2 is `j = (m + n + 1) / 2 - i`.
//   3. Let:
//      - left1 = max element in left half of nums1 (nums1[i-1] or INT_MIN if empty)
//      - right1 = min element in right half of nums1 (nums1[i] or INT_MAX if empty)
//      - left2 = max element in left half of nums2 (nums2[j-1] or INT_MIN if empty)
//      - right2 = min element in right half of nums2 (nums2[j] or INT_MAX if empty)
//   4. A valid partition satisfies: left1 <= right2 AND left2 <= right1.
//      - If left1 > right2, we partitioned too far right in nums1, so we move left: hi = i - 1.
//      - If left2 > right1, we partitioned too far left in nums1, so we move right: lo = i + 1.
//   5. Once a valid partition is found:
//      - If total elements (m+n) is odd, median is max(left1, left2).
//      - If even, median is (max(left1, left2) + min(right1, right2)) / 2.0.
//
// Time Complexity: O(log(min(m, n))) — binary search is run on the smaller array.
// Space Complexity: O(1) — only pointers/variables are used.
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

int testNum = 0;
void check(double gotOpt, double gotAlt, double expected, const string& desc) {
    ++testNum;
    bool passOpt = (abs(gotOpt - expected) < 1e-6);
    bool passAlt = (abs(gotAlt - expected) < 1e-6);
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
    
    // Test 1: Odd total length, simple overlapping
    {
        vector<int> n1 = {1, 3};
        vector<int> n2 = {2};
        check(solver.findMedianSortedArrays(n1, n2),
              solverAlt.findMedianSortedArrays(n1, n2),
              2.0, "Odd total length: nums1=[1,3], nums2=[2]");
    }
    
    // Test 2: Even total length, simple disjoint
    {
        vector<int> n1 = {1, 2};
        vector<int> n2 = {3, 4};
        check(solver.findMedianSortedArrays(n1, n2),
              solverAlt.findMedianSortedArrays(n1, n2),
              2.5, "Even total length: nums1=[1,2], nums2=[3,4]");
    }
    
    // Test 3: Empty first array, odd length
    {
        vector<int> n1 = {};
        vector<int> n2 = {1};
        check(solver.findMedianSortedArrays(n1, n2),
              solverAlt.findMedianSortedArrays(n1, n2),
              1.0, "Empty first array: nums1=[], nums2=[1]");
    }
    
    // Test 4: Empty second array, even length
    {
        vector<int> n1 = {2, 3};
        vector<int> n2 = {};
        check(solver.findMedianSortedArrays(n1, n2),
              solverAlt.findMedianSortedArrays(n1, n2),
              2.5, "Empty second array: nums1=[2,3], nums2=[]");
    }
    
    // Test 5: Single element arrays
    {
        vector<int> n1 = {1};
        vector<int> n2 = {2};
        check(solver.findMedianSortedArrays(n1, n2),
              solverAlt.findMedianSortedArrays(n1, n2),
              1.5, "Single element arrays: nums1=[1], nums2=[2]");
    }
    
    // Test 6: Fully disjoint / non-overlapping arrays
    {
        vector<int> n1 = {1, 2, 3};
        vector<int> n2 = {4, 5, 6};
        check(solver.findMedianSortedArrays(n1, n2),
              solverAlt.findMedianSortedArrays(n1, n2),
              3.5, "Disjoint arrays: nums1=[1,2,3], nums2=[4,5,6]");
    }
    
    // Test 7: Alternating elements (interleaved)
    {
        vector<int> n1 = {1, 5, 9};
        vector<int> n2 = {2, 6, 10};
        check(solver.findMedianSortedArrays(n1, n2),
              solverAlt.findMedianSortedArrays(n1, n2),
              5.5, "Interleaved arrays: nums1=[1,5,9], nums2=[2,6,10]");
    }
    
    // Test 8: Multiple duplicate elements
    {
        vector<int> n1 = {1, 2};
        vector<int> n2 = {1, 2, 3};
        check(solver.findMedianSortedArrays(n1, n2),
              solverAlt.findMedianSortedArrays(n1, n2),
              2.0, "Duplicate elements: nums1=[1,2], nums2=[1,2,3]");
    }

    return 0;
}


