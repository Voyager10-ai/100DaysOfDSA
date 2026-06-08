#include <iostream>
#include <vector>

using namespace std;

// LeetCode 74 – Search a 2D Matrix
// Given an m x n matrix with the following properties:
//   - Each row is sorted in non-decreasing order.
//   - The first integer of each row is greater than the last integer of the
//     previous row.
// Given a target value, return true if target is in the matrix, else false.
//
// Algorithm: Treat the 2D matrix as a virtual 1D sorted array and apply
//            standard binary search.
//   1. Let total = m * n elements. Use lo = 0, hi = total - 1.
//   2. Compute mid index, then map it to (row, col) via:
//        row = mid / n,  col = mid % n
//   3. Compare matrix[row][col] with target and narrow the search space.
//
// Time Complexity:  O(log(m * n)) — binary search over all elements
// Space Complexity: O(1) — only a few variables

class Solution {
public:
    // Searches for target in the sorted 2D matrix
    // Returns true if target exists, false otherwise
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false;

        int m = matrix.size();       // number of rows
        int n = matrix[0].size();    // number of columns
        int lo = 0, hi = m * n - 1;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            int row = mid / n;
            int col = mid % n;
            int val = matrix[row][col];

            if (val == target) {
                return true;
            } else if (val < target) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        return false;
    }
};

// Helper to run a test case
void runTest(int id, vector<vector<int>> matrix, int target, bool expected) {
    Solution sol;
    bool result = sol.searchMatrix(matrix, target);
    cout << "Test " << id << ": " << (result == expected ? "PASS" : "FAIL")
         << " (got " << result << ", expected " << expected << ")" << endl;
}

int main() {
    // Test 1: LeetCode Example 1 – target present
    runTest(1, {{1,3,5,7},{10,11,16,20},{23,30,34,60}}, 3, true);

    // Test 2: LeetCode Example 2 – target not present
    runTest(2, {{1,3,5,7},{10,11,16,20},{23,30,34,60}}, 13, false);

    // Test 3: Single element matrix – found
    runTest(3, {{5}}, 5, true);

    // Test 4: Single element matrix – not found
    runTest(4, {{5}}, 3, false);

    // Test 5: Target is the very first element
    runTest(5, {{1,3,5},{7,9,11},{13,15,17}}, 1, true);

    // Test 6: Target is the very last element
    runTest(6, {{1,3,5},{7,9,11},{13,15,17}}, 17, true);

    return 0;
}
