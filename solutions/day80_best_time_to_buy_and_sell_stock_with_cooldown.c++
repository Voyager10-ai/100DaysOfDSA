#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) return 0;

        // Space-optimized: only need previous day's states
        int hold = -prices[0];
        int sold = 0;
        int rest = 0;

        for (int i = 1; i < n; ++i) {
            int prevHold = hold;
            int prevSold = sold;
            int prevRest = rest;

            hold = max(prevHold, prevRest - prices[i]);
            sold = prevHold + prices[i];
            rest = max(prevRest, prevSold);
        }

        return max(sold, rest);
    }
};

int main() {
    Solution sol;

    vector<int> prices1 = {1, 2, 3, 0, 2};
    cout << "Test 1: " << sol.maxProfit(prices1) << " (Expected: 3)" << endl;

    vector<int> prices2 = {1};
    cout << "Test 2: " << sol.maxProfit(prices2) << " (Expected: 0)" << endl;

    vector<int> prices3 = {1, 2, 4};
    cout << "Test 3: " << sol.maxProfit(prices3) << " (Expected: 3)" << endl;

    vector<int> prices4 = {2, 1, 4, 5, 2, 9, 7};
    cout << "Test 4: " << sol.maxProfit(prices4) << " (Expected: 11)" << endl;

    vector<int> prices5 = {6, 1, 3, 2, 4, 7};
    cout << "Test 5: " << sol.maxProfit(prices5) << " (Expected: 6)" << endl;

    return 0;
}
