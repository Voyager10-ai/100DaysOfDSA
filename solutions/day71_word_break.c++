#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        int n = s.length();
        vector<bool> dp(n + 1, false);
        dp[0] = true;
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (dp[j] && wordSet.find(s.substr(j, i - j)) != wordSet.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }
        
        return dp[n];
    }
};

int main() {
    Solution solution;
    
    string s1 = "leetcode";
    vector<string> wordDict1 = {"leet", "code"};
    cout << "Test 1: " << (solution.wordBreak(s1, wordDict1) ? "Pass" : "Fail") << endl;
    
    string s2 = "applepenapple";
    vector<string> wordDict2 = {"apple", "pen"};
    cout << "Test 2: " << (solution.wordBreak(s2, wordDict2) ? "Pass" : "Fail") << endl;

    string s3 = "catsandog";
    vector<string> wordDict3 = {"cats", "dog", "sand", "and", "cat"};
    cout << "Test 3: " << (!solution.wordBreak(s3, wordDict3) ? "Pass" : "Fail") << endl;
    
    return 0;
}
