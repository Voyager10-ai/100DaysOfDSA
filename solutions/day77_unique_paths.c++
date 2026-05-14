#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1);
        
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[j] += dp[j - 1];
            }
        }
        
        return dp[n - 1];
    }
};

int main() {
    Solution sol;
    
    int m1 = 3, n1 = 7;
    int m2 = 3, n2 = 2;
    
    cout << "Test case 1 (m=" << m1 << ", n=" << n1 << "): " << sol.uniquePaths(m1, n1) << " (Expected: 28)" << endl;
    cout << "Test case 2 (m=" << m2 << ", n=" << n2 << "): " << sol.uniquePaths(m2, n2) << " (Expected: 3)" << endl;
    
    return 0;
}
