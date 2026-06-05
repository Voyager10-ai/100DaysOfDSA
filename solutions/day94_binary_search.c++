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

// Helper to run a test case
void runTest(int id, vector<int> nums, int target, int expected) {
    Solution sol;
    int result = sol.search(nums, target);
    cout << "Test " << id << ": " << (result == expected ? "PASS" : "FAIL")
         << " (got " << result << ", expected " << expected << ")" << endl;
}

int main() {
    // Test 1: LeetCode Example 1 – target in the middle
    runTest(1, {-1,0,3,5,9,12}, 9, 4);

    // Test 2: LeetCode Example 2 – target not present
    runTest(2, {-1,0,3,5,9,12}, 2, -1);

    // Test 3: Single element – found
    runTest(3, {5}, 5, 0);

    // Test 4: Single element – not found
    runTest(4, {5}, 3, -1);

    // Test 5: Target is the first element
    runTest(5, {1,2,3,4,5,6,7}, 1, 0);

    // Test 6: Target is the last element
    runTest(6, {1,2,3,4,5,6,7}, 7, 6);

    // Test 7: Two elements – target is first
    runTest(7, {1,3}, 1, 0);

    // Test 8: Two elements – target is second
    runTest(8, {1,3}, 3, 1);

    // Test 9: Two elements – target not present (between them)
    runTest(9, {1,3}, 2, -1);

    // Test 10: Target smaller than all elements
    runTest(10, {10,20,30,40,50}, 5, -1);

    // Test 11: Target larger than all elements
    runTest(11, {10,20,30,40,50}, 55, -1);

    // Test 12: All negative numbers – target found
    runTest(12, {-100,-50,-20,-10,-5}, -20, 2);

    // Test 13: All negative numbers – target not found
    runTest(13, {-100,-50,-20,-10,-5}, -30, -1);

    // Test 14: Even-length array – target at mid-left
    runTest(14, {2,4,6,8,10,12}, 6, 2);

    // Test 15: Large array – target near the end
    vector<int> large(10000);
    for (int i = 0; i < 10000; ++i) large[i] = i * 2;
    runTest(15, large, 19998, 9999);

    // Test 16: Large array – target not present
    runTest(16, large, 7, -1);

    return 0;
}
