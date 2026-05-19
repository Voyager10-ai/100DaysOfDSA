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
