/*
 * Day 66: N-Queens
 * 
 * Problem: Place n queens on an n×n chessboard such that no two queens
 *          attack each other (no shared row, column, or diagonal).
 *          Return all distinct solutions.
 * 
 * Approach: Backtracking (row-by-row placement)
 *   - Place one queen per row, trying each column
 *   - For each placement, check safety: no queen in same column,
 *     upper-left diagonal, or upper-right diagonal
 *   - If safe, recurse to the next row; otherwise backtrack
 *   - Time Complexity: O(n!) — pruned permutation search
 *   - Space Complexity: O(n^2) for the board
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
    unordered_set<int> cols;      // Columns with queens
    unordered_set<int> diag1;     // row - col diagonals (\)
    unordered_set<int> diag2;     // row + col anti-diagonals (/)

    void backtrack(int n, int row, vector<string>& board, vector<vector<string>>& result) {
        // Base case: all queens are placed
        if (row == n) {
            result.push_back(board);
            return;
        }

        for (int col = 0; col < n; ++col) {
            // O(1) conflict check using hash sets
            if (cols.count(col) || diag1.count(row - col) || diag2.count(row + col))
                continue;

            board[row][col] = 'Q';
            cols.insert(col);
            diag1.insert(row - col);
            diag2.insert(row + col);

            backtrack(n, row + 1, board, result);

            // Backtrack
            board[row][col] = '.';
            cols.erase(col);
            diag1.erase(row - col);
            diag2.erase(row + col);
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> result;
        vector<string> board(n, string(n, '.'));
        cols.clear(); diag1.clear(); diag2.clear();
        backtrack(n, 0, board, result);
        return result;
    }
};

int main() {
    Solution sol;

    // Test Case 1: n = 4
    int n1 = 4;
    vector<vector<string>> result1 = sol.solveNQueens(n1);
    cout << "Input: n = " << n1 << endl;
    cout << "Number of solutions: " << result1.size() << endl;
    for (int s = 0; s < result1.size(); ++s) {
        cout << "Solution " << s + 1 << ":" << endl;
        for (const string& row : result1[s]) {
            cout << "  " << row << endl;
        }
        cout << endl;
    }

    // Test Case 2: n = 1
    int n2 = 1;
    vector<vector<string>> result2 = sol.solveNQueens(n2);
    cout << "Input: n = " << n2 << endl;
    cout << "Number of solutions: " << result2.size() << endl;
    for (int s = 0; s < result2.size(); ++s) {
        cout << "Solution " << s + 1 << ":" << endl;
        for (const string& row : result2[s]) {
            cout << "  " << row << endl;
        }
        cout << endl;
    }

    // Test Case 3: n = 8 (classic 8-Queens, expected 92 solutions)
    int n3 = 8;
    vector<vector<string>> result3 = sol.solveNQueens(n3);
    cout << "Input: n = " << n3 << endl;
    cout << "Number of solutions: " << result3.size() << " (expected 92)" << endl;

    return 0;
}
