#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    // O(n) time complexity, O(1) space complexity (fixed size array of 26)
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) {
            return false;
        }
        
        vector<int> count(26, 0);
        
        // Increment frequency for 's' and decrement for 't'
        for (int i = 0; i < s.length(); i++) {
            count[s[i] - 'a']++;
            count[t[i] - 'a']--;
        }
        
        // If they are valid anagrams, all counts should be exactly 0
        for (int i = 0; i < 26; i++) {
            if (count[i] != 0) {
                return false;
            }
        }
        
        return true;
    }
};
