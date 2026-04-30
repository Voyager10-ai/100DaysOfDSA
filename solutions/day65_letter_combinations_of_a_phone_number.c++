/*
 * Day 65: Letter Combinations of a Phone Number
 * 
 * Problem: Given a string containing digits from 2-9 inclusive,
 *          return all possible letter combinations that the number could represent.
 * 
 * Approach: Backtracking
 *   - Map each digit to its corresponding letters (like a phone keypad)
 *   - Recursively build combinations by choosing one letter per digit
 *   - Time Complexity: O(4^n) where n = number of digits (worst case digit maps to 4 letters)
 *   - Space Complexity: O(n) for recursion depth
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Solution {
    // Mapping of digits to corresponding letters (like a phone keypad)
    vector<string> digitToLetters = {
        "",     // 0
        "",     // 1
        "abc",  // 2
        "def",  // 3
        "ghi",  // 4
        "jkl",  // 5
        "mno",  // 6
        "pqrs", // 7
        "tuv",  // 8
        "wxyz"  // 9
    };

    void backtrack(string& digits, int index, string& current, vector<string>& result) {
        // Base case: if current combination is complete
        if (index == digits.length()) {
            result.push_back(current);
            return;
        }

        // Get the letters corresponding to the current digit
        string letters = digitToLetters[digits[index] - '0'];

        // Try each letter for the current digit
        for (char letter : letters) {
            current.push_back(letter);
            backtrack(digits, index + 1, current, result);
            current.pop_back(); // Backtrack: remove last letter
        }
    }

public:
    vector<string> letterCombinations(string digits) {
        vector<string> result;
        if (digits.empty()) return result;

        string current;
        backtrack(digits, 0, current, result);
        return result;
    }
};

int main() {
    Solution sol;

    // Test Case 1: digits = "23"
    string digits1 = "23";
    vector<string> result1 = sol.letterCombinations(digits1);
    cout << "Input: \"" << digits1 << "\"" << endl;
    cout << "Output: [";
    for (int i = 0; i < result1.size(); ++i) {
        cout << "\"" << result1[i] << "\"";
        if (i < result1.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    // Test Case 2: digits = ""
    string digits2 = "";
    vector<string> result2 = sol.letterCombinations(digits2);
    cout << "\nInput: \"" << digits2 << "\"" << endl;
    cout << "Output: [";
    for (int i = 0; i < result2.size(); ++i) {
        cout << "\"" << result2[i] << "\"";
        if (i < result2.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    // Test Case 3: digits = "2"
    string digits3 = "2";
    vector<string> result3 = sol.letterCombinations(digits3);
    cout << "\nInput: \"" << digits3 << "\"" << endl;
    cout << "Output: [";
    for (int i = 0; i < result3.size(); ++i) {
        cout << "\"" << result3[i] << "\"";
        if (i < result3.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    // Test Case 4: digits = "79" (4-letter mappings)
    string digits4 = "79";
    vector<string> result4 = sol.letterCombinations(digits4);
    cout << "\nInput: \"" << digits4 << "\"" << endl;
    cout << "Output: [";
    for (int i = 0; i < result4.size(); ++i) {
        cout << "\"" << result4[i] << "\"";
        if (i < result4.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    return 0;
}
