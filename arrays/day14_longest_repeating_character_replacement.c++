#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // O(n) time complexity, O(1) space complexity (since we only store 26 characters)
    int characterReplacement(string s, int k) {
        vector<int> count(26, 0);
        int maxL = 0;
        int maxCount = 0;
        int left = 0;
        
        for (int right = 0; right < s.length(); right++) {
            count[s[right] - 'A']++;
            maxCount = max(maxCount, count[s[right] - 'A']);
            
            // If the current window size minus the most frequent character count
            // is greater than k, we need to shrink the window
            if ((right - left + 1) - maxCount > k) {
                count[s[left] - 'A']--;
                left++;
            }
            
            maxL = max(maxL, right - left + 1);
        }
        
        return maxL;
    }
};
