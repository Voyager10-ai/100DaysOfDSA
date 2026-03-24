#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int countSubstrings(string s) {
        int count = 0;
        for (int i = 0; i < s.length(); i++) {
            // Check for odd length palindromes (centered at i)
            int left = i, right = i;
            while (left >= 0 && right < s.length() && s[left] == s[right]) {
                count++;
                left--;
                right++;
            }
            
            // Check for even length palindromes (centered between i and i+1)
            left = i; right = i + 1;
            while (left >= 0 && right < s.length() && s[left] == s[right]) {
                count++;
                left--;
                right++;
            }
        }
        return count;
    }
};

int main() {
    Solution sol;
    string s1 = "abc";
    string s2 = "aaa";
    
    cout << "Number of palindromic substrings in \"" << s1 << "\": " << sol.countSubstrings(s1) << endl;
    cout << "Number of palindromic substrings in \"" << s2 << "\": " << sol.countSubstrings(s2) << endl;
    
    return 0;
}
