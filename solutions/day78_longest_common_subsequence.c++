#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.length();
        int n = text2.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        return dp[m][n];
    }
};

int main() {
    Solution sol;
    
    string text1_1 = "abcde", text2_1 = "ace";
    string text1_2 = "abc", text2_2 = "abc";
    string text1_3 = "abc", text2_3 = "def";
    
    cout << "Test case 1: " << sol.longestCommonSubsequence(text1_1, text2_1) << " (Expected: 3)" << endl;
    cout << "Test case 2: " << sol.longestCommonSubsequence(text1_2, text2_2) << " (Expected: 3)" << endl;
    cout << "Test case 3: " << sol.longestCommonSubsequence(text1_3, text2_3) << " (Expected: 0)" << endl;
    
    return 0;
}
