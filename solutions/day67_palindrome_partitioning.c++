/*
 * Day 67: Palindrome Partitioning
 * 
 * Problem: Given a string s, partition s such that every substring of the
 *          partition is a palindrome. Return all possible palindrome partitionings.
 * 
 * Approach: Backtracking
 *   - At each position, try every possible substring starting there
 *   - Only recurse if the current substring is a palindrome
 *   - When we reach the end of the string, we have a valid partition
 *   - Time Complexity: O(n * 2^n) — 2^n possible partitions, O(n) palindrome check
 *   - Space Complexity: O(n) for recursion depth
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
    vector<vector<bool>> dp; // dp[i][j] = true if s[i..j] is a palindrome

    void buildPalindromeTable(string& s) {
        int n = s.length();
        dp.assign(n, vector<bool>(n, false));

        // Every single character is a palindrome
        for (int i = 0; i < n; ++i) dp[i][i] = true;

        // Check substrings of length 2+
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                if (s[i] == s[j]) {
                    dp[i][j] = (len == 2) || dp[i + 1][j - 1];
                }
            }
        }
    }

    void backtrack(string& s, int start, vector<string>& partition, vector<vector<string>>& result) {
        // Base case: reached end of string, current partition is valid
        if (start == s.length()) {
            result.push_back(partition);
            return;
        }

        // Try every possible substring starting from 'start'
        for (int end = start; end < s.length(); ++end) {
            if (dp[start][end]) { // O(1) palindrome check via DP table
                partition.push_back(s.substr(start, end - start + 1));
                backtrack(s, end + 1, partition, result);
                partition.pop_back(); // Backtrack
            }
        }
    }

public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> result;
        vector<string> current;
        buildPalindromeTable(s);
        backtrack(s, 0, current, result);
        return result;
    }
};
// Helper to print partition results
void printResult(const string& input, const vector<vector<string>>& result) {
    cout << "Input: \"" << input << "\"" << endl;
    cout << "Number of partitions: " << result.size() << endl;
    cout << "Output: [";
    for (int i = 0; i < result.size(); ++i) {
        cout << "[";
        for (int j = 0; j < result[i].size(); ++j) {
            cout << "\"" << result[i][j] << "\"";
            if (j < result[i].size() - 1) cout << ", ";
        }
        cout << "]";
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl << endl;
}

int main() {
    Solution sol;

    // Test Case 1: s = "aab" → [["a","a","b"], ["aa","b"]]
    string s1 = "aab";
    printResult(s1, sol.partition(s1));

    // Test Case 2: s = "a" → [["a"]]
    string s2 = "a";
    printResult(s2, sol.partition(s2));

    // Test Case 3: s = "racecar" (full palindrome string)
    string s3 = "racecar";
    printResult(s3, sol.partition(s3));

    return 0;
}
