#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // O(n) time complexity, O(m) space complexity, where m is the character set size (e.g., 128 for ASCII)
    int lengthOfLongestSubstring(string s) {
        vector<int> charIndex(128, -1);
        int maxLength = 0;
        int left = 0;
        
        for (int right = 0; right < s.length(); right++) {
            // If the character is already in the substring, move the left pointer
            if (charIndex[s[right]] >= left) {
                left = charIndex[s[right]] + 1;
            }
            
            // Update the latest index of the character
            charIndex[s[right]] = right;
            
            // Calculate maximum length encountered so far
            maxLength = max(maxLength, right - left + 1);
        }
        
        return maxLength;
    }
};
