#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) return n;
        int prev1 = 2; // ways to reach step 2
        int prev2 = 1; // ways to reach step 1
        int current = 0;
        
        for (int i = 3; i <= n; i++) {
            current = prev1 + prev2;
            prev2 = prev1;
            prev1 = current;
        }
        
        return current;
    }
};

int main() {
    Solution sol;
    int n = 2;
    cout << "Ways to climb " << n << " stairs: " << sol.climbStairs(n) << endl;
    return 0;
}
