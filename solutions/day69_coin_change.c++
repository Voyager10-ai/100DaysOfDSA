/*
 * Problem: Coin Change
 * Day: 69
 * 
 * Description:
 * You are given an integer array coins representing coins of different denominations 
 * and an integer amount representing a total amount of money.
 * Return the fewest number of coins that you need to make up that amount.
 * If that amount of money cannot be made up by any combination of the coins, return -1.
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // Coin Change using Dynamic Programming (Bottom-Up approach)
    // Time Complexity: O(amount * N) where N is the number of coins
    // Space Complexity: O(amount) for the DP array
    int coinChange(vector<int>& coins, int amount) {
        // dp[i] will be storing the fewest number of coins need to make up amount i
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0; // 0 coins are needed to make amount 0
        
        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                if (i - coin >= 0) {
                    dp[i] = min(dp[i], dp[i - coin] + 1);
                }
            }
        }
        
        // If dp[amount] is still amount + 1, it means the amount cannot be made
        return dp[amount] > amount ? -1 : dp[amount];
    }
};

int main() {
    Solution sol;
    
    // Test Case 1
    vector<int> coins1 = {1, 2, 5};
    int amount1 = 11;
    cout << "Input: coins = [1, 2, 5], amount = 11\nOutput: " << sol.coinChange(coins1, amount1) << "\nExpected: 3\n\n";
    
    // Test Case 2
    vector<int> coins2 = {2};
    int amount2 = 3;
    cout << "Input: coins = [2], amount = 3\nOutput: " << sol.coinChange(coins2, amount2) << "\nExpected: -1\n\n";

    // Test Case 3
    vector<int> coins3 = {1};
    int amount3 = 0;
    cout << "Input: coins = [1], amount = 0\nOutput: " << sol.coinChange(coins3, amount3) << "\nExpected: 0\n\n";

    return 0;
}
