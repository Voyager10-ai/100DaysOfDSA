#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Time Complexity: O(N) where N is the length of the prices array
    // Space Complexity: O(1) since we are using only a few variables
    int maxProfit(vector<int>& prices) {
        int minPrice = prices[0];
        int maxPro = 0;
        
        for (int i = 1; i < prices.size(); i++) {
            maxPro = max(maxPro, prices[i] - minPrice);
            minPrice = min(minPrice, prices[i]);
        }
        
        return maxPro;
    }
};
