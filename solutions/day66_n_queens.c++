#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
    void backtrack(int n, int row, vector<string>& board, vector<vector<string>>& result) {
        // Base case: all queens are placed
        if (row == n) {
            result.push_back(board);
            return;
        }

        for (int col = 0; col < n; ++col) {
            if (isSafe(board, row, col, n)) {
                board[row][col] = 'Q';
                backtrack(n, row + 1, board, result);
                board[row][col] = '.'; // Backtrack
            }
        }
    }

    bool isSafe(vector<string>& board, int row, int col, int n) {
        // Check column above
        for (int i = 0; i < row; ++i) {
            if (board[i][col] == 'Q') return false;
        }

        // Check upper-left diagonal
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j) {
            if (board[i][j] == 'Q') return false;
        }

        // Check upper-right diagonal
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; --i, ++j) {
            if (board[i][j] == 'Q') return false;
        }

        return true;
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> result;
        vector<string> board(n, string(n, '.'));
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

    return 0;
}
