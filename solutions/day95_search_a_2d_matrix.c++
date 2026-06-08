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
