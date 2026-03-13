#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";

        int start = 0, maxLen = 1;

        for (int i = 0; i < s.length(); i++) {
            // Check for odd length palindromes (centered at i)
            int left = i, right = i;
            while (left >= 0 && right < s.length() && s[left] == s[right]) {
                if (right - left + 1 > maxLen) {
                    start = left;
                    maxLen = right - left + 1;
                }
                left--;
                right++;
            }

            // Check for even length palindromes (centered between i and i+1)
            left = i; right = i + 1;
            while (left >= 0 && right < s.length() && s[left] == s[right]) {
                if (right - left + 1 > maxLen) {
                    start = left;
                    maxLen = right - left + 1;
                }
                left--;
                right++;
            }
        }

        return s.substr(start, maxLen);
    }
};

int main() {
    Solution sol;
    string s = "babad";
    cout << "Longest Palindromic Substring of " << s << " is: " << sol.longestPalindrome(s) << endl;
    return 0;
}
