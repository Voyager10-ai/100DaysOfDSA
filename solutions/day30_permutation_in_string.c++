#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    // Time Complexity: O(N) where N is the length of string s2
    // Space Complexity: O(1) since we use two vectors of constant size 26
    bool checkInclusion(string s1, string s2) {
        if (s1.length() > s2.length()) return false;
        
        vector<int> s1Count(26, 0), s2Count(26, 0);
        
        for (int i = 0; i < s1.length(); i++) {
            s1Count[s1[i] - 'a']++;
            s2Count[s2[i] - 'a']++;
        }
        
        for (int i = 0; i < s2.length() - s1.length(); i++) {
            if (s1Count == s2Count) return true;
            s2Count[s2[i] - 'a']--;
            s2Count[s2[i + s1.length()] - 'a']++;
        }
        
        return s1Count == s2Count;
    }
};
