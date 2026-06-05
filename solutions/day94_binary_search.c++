#include <iostream>
#include <vector>

using namespace std;

// LeetCode 704 – Binary Search
// Given a sorted array of integers and a target value, return the index
// of the target if found, otherwise return -1.
//
// Algorithm: Classic Binary Search
//   1. Maintain two pointers lo and hi bounding the search space.
//   2. Compute mid = lo + (hi - lo) / 2 to avoid integer overflow.
//   3. If nums[mid] == target, return mid.
//   4. If nums[mid] < target, search the right half (lo = mid + 1).
//   5. If nums[mid] > target, search the left half (hi = mid - 1).
//   6. If lo > hi, target is not in the array — return -1.
//
// Time Complexity:  O(log n) — halves search space each iteration
// Space Complexity: O(1) — only uses a few variables

class Solution {
public:
    // Searches for target in sorted array nums
    // Returns index of target, or -1 if not found
    int search(vector<int>& nums, int target) {
        int lo = 0, hi = nums.size() - 1;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;  // avoids overflow vs (lo+hi)/2

            if (nums[mid] == target) {
                return mid;          // found it
            } else if (nums[mid] < target) {
                lo = mid + 1;        // target is in the right half
            } else {
                hi = mid - 1;        // target is in the left half
            }
        }

        return -1;  // target not found
    }
};

int main() {
    return 0;
}
