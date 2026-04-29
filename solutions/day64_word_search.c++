#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
    bool dfs(vector<vector<char>>& board, string& word, int i, int j, int index) {
        if (index == word.length()) return true;
        
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || board[i][j] != word[index]) {
            return false;
        }
        
        char temp = board[i][j];
        board[i][j] = '*'; // Mark as visited to prevent reuse in current path
        
        bool found = dfs(board, word, i + 1, j, index + 1) ||
                     dfs(board, word, i - 1, j, index + 1) ||
                     dfs(board, word, i, j + 1, index + 1) ||
                     dfs(board, word, i, j - 1, index + 1);
                     
        board[i][j] = temp; // Restore original character
        
        return found;
    }

public:
    bool exist(vector<vector<char>>& board, string word) {
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                // Start DFS if the first character matches
                if (board[i][j] == word[0] && dfs(board, word, i, j, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    Solution sol;
    vector<vector<char>> board = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };
    
    string word1 = "ABCCED";
    string word2 = "SEE";
    string word3 = "ABCB";
    
    cout << "Word: " << word1 << " Exists: " << (sol.exist(board, word1) ? "true" : "false") << endl;
    cout << "Word: " << word2 << " Exists: " << (sol.exist(board, word2) ? "true" : "false") << endl;
    cout << "Word: " << word3 << " Exists: " << (sol.exist(board, word3) ? "true" : "false") << endl;
    
    return 0;
}
