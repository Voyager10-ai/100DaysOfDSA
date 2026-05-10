#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int numDecodings(string s) {
        if (s.empty() || s[0] == '0') {
            return 0;
        }
        
        int n = s.length();
        vector<int> dp(n + 1, 0);
        
        dp[0] = 1;
        dp[1] = 1;
        
        for (int i = 2; i <= n; ++i) {
            int singleDigit = s[i - 1] - '0';
            int doubleDigit = (s[i - 2] - '0') * 10 + (s[i - 1] - '0');
            
            if (singleDigit >= 1 && singleDigit <= 9) {
                dp[i] += dp[i - 1];
            }
            
            if (doubleDigit >= 10 && doubleDigit <= 26) {
                dp[i] += dp[i - 2];
            }
        }
        
        return dp[n];
    }
};

int main() {
    Solution solution;
    
    string s1 = "12";
    cout << "Test 1: " << (solution.numDecodings(s1) == 2 ? "Pass" : "Fail") << endl;
    
    string s2 = "226";
    cout << "Test 2: " << (solution.numDecodings(s2) == 3 ? "Pass" : "Fail") << endl;
    
    string s3 = "06";
    cout << "Test 3: " << (solution.numDecodings(s3) == 0 ? "Pass" : "Fail") << endl;
    
    return 0;
}
