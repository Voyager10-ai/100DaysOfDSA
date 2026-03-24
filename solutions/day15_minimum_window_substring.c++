#include <string>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    // O(M + N) time complexity, O(1) space complexity (fixed size array of 128)
    string minWindow(string s, string t) {
        if (s.empty() || t.empty() || s.length() < t.length()) {
            return "";
        }

        vector<int> map(128, 0);
        for (char c : t) {
            map[c]++;
        }

        int left = 0, right = 0;
        // Count of characters in 't' that need to be matched
        int count = t.length(); 
        int minLen = INT_MAX;
        int startIndex = 0;

        while (right < s.length()) {
            // If the current character is in 't' and we still need it, decrease the remaining count
            if (map[s[right]] > 0) {
                count--;
            }
            // Decrease the frequency of the current character in the map
            map[s[right]]--;
            right++;

            // When all characters of 't' are successfully matched
            while (count == 0) {
                // Update minimum window length and its start index
                if (right - left < minLen) {
                    minLen = right - left;
                    startIndex = left;
                }

                // Restore the character at the left pointer into the map
                map[s[left]]++;
                // If the restored character is part of 't' and is now missing in the window,
                // we need to find it again, so increment the count
                if (map[s[left]] > 0) {
                    count++;
                }
                left++;
            }
        }

        return minLen == INT_MAX ? "" : s.substr(startIndex, minLen);
    }
};
