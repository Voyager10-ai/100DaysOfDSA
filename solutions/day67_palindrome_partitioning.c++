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
    bool isPalindrome(string& s, int left, int right) {
        while (left < right) {
            if (s[left] != s[right]) return false;
            ++left;
            --right;
        }
        return true;
    }

    void backtrack(string& s, int start, vector<string>& partition, vector<vector<string>>& result) {
        // Base case: reached end of string, current partition is valid
        if (start == s.length()) {
            result.push_back(partition);
            return;
        }

        // Try every possible substring starting from 'start'
        for (int end = start; end < s.length(); ++end) {
            if (isPalindrome(s, start, end)) {
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
        backtrack(s, 0, current, result);
        return result;
    }
};

int main() {
    Solution sol;

    // Test Case 1: s = "aab"
    string s1 = "aab";
    vector<vector<string>> result1 = sol.partition(s1);
    cout << "Input: \"" << s1 << "\"" << endl;
    cout << "Output: [";
    for (int i = 0; i < result1.size(); ++i) {
        cout << "[";
        for (int j = 0; j < result1[i].size(); ++j) {
            cout << "\"" << result1[i][j] << "\"";
            if (j < result1[i].size() - 1) cout << ", ";
        }
        cout << "]";
        if (i < result1.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    // Test Case 2: s = "a"
    string s2 = "a";
    vector<vector<string>> result2 = sol.partition(s2);
    cout << "\nInput: \"" << s2 << "\"" << endl;
    cout << "Output: [";
    for (int i = 0; i < result2.size(); ++i) {
        cout << "[";
        for (int j = 0; j < result2[i].size(); ++j) {
            cout << "\"" << result2[i][j] << "\"";
            if (j < result2[i].size() - 1) cout << ", ";
        }
        cout << "]";
        if (i < result2.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    // Test Case 3: s = "racecar" (full palindrome string)
    string s3 = "racecar";
    vector<vector<string>> result3 = sol.partition(s3);
    cout << "\nInput: \"" << s3 << "\"" << endl;
    cout << "Number of partitions: " << result3.size() << endl;
    cout << "Output: [";
    for (int i = 0; i < result3.size(); ++i) {
        cout << "[";
        for (int j = 0; j < result3[i].size(); ++j) {
            cout << "\"" << result3[i][j] << "\"";
            if (j < result3[i].size() - 1) cout << ", ";
        }
        cout << "]";
        if (i < result3.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    return 0;
}
