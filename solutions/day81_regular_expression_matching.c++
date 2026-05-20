#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.length();
        int n = p.length();

        // dp[i][j] = true if s[0..i-1] matches p[0..j-1]
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));

        // Empty string matches empty pattern
        dp[0][0] = true;

        // Handle patterns like a*, a*b*, a*b*c* that can match empty string
        for (int j = 2; j <= n; ++j) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 2];
            }
        }

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] == '.' || p[j - 1] == s[i - 1]) {
                    // Direct character match or '.' wildcard
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (p[j - 1] == '*') {
                    // '*' can mean zero occurrences of preceding element
                    dp[i][j] = dp[i][j - 2];

                    // Or one+ occurrences if preceding element matches current char
                    if (p[j - 2] == '.' || p[j - 2] == s[i - 1]) {
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                }
            }
        }

        return dp[m][n];
    }
};

int main() {
    Solution sol;

    // Basic test cases
    cout << "Test 1: " << (sol.isMatch("aa", "a") ? "true" : "false") << " (Expected: false)" << endl;
    cout << "Test 2: " << (sol.isMatch("aa", "a*") ? "true" : "false") << " (Expected: true)" << endl;
    cout << "Test 3: " << (sol.isMatch("ab", ".*") ? "true" : "false") << " (Expected: true)" << endl;

    return 0;
}
