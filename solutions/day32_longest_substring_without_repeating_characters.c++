#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Time Complexity: O(N) where N is the length of the string s
    // Space Complexity: O(1) or O(M) where M is the charset size (const 256)
    int lengthOfLongestSubstring(string s) {
        vector<int> charIndex(256, -1);
        int maxLength = 0;
        int left = 0;
        
        for (int right = 0; right < s.length(); right++) {
            if (charIndex[s[right]] != -1) {
                left = max(left, charIndex[s[right]] + 1);
            }
            charIndex[s[right]] = right;
            maxLength = max(maxLength, right - left + 1);
        }
        
        return maxLength;
    }
};
