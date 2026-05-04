#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // Climbing Stairs using Dynamic Programming (Bottom-Up approach)
    // Time Complexity: O(N) where N is the number of stairs
    // Space Complexity: O(1) since we only use two variables to store previous results
    int climbStairs(int n) {
        if (n <= 2) return n;
        
        int prev1 = 2; // Ways to reach step 2
        int prev2 = 1; // Ways to reach step 1
        int current = 0;
        
        for (int i = 3; i <= n; i++) {
            current = prev1 + prev2; // The number of ways to reach current step is the sum of ways to reach the previous two steps
            prev2 = prev1;
            prev1 = current;
        }
        
        return current;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1
    int n1 = 2;
    cout << "Input: n = " << n1 << "\nOutput: " << sol.climbStairs(n1) << "\nExpected: 2\n\n";
    
    // Test Case 2
    int n2 = 3;
    cout << "Input: n = " << n2 << "\nOutput: " << sol.climbStairs(n2) << "\nExpected: 3\n\n";

    // Test Case 3
    int n3 = 5;
    cout << "Input: n = " << n3 << "\nOutput: " << sol.climbStairs(n3) << "\nExpected: 8\n\n";

    // Test Case 4
    int n4 = 1;
    cout << "Input: n = " << n4 << "\nOutput: " << sol.climbStairs(n4) << "\nExpected: 1\n\n";

    return 0;
}
