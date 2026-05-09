#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    int robLinear(vector<int>& nums, int start, int end) {
        int prev1 = 0;
        int prev2 = 0;
        
        for (int i = start; i <= end; ++i) {
            int current = max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = current;
        }
        
        return prev1;
    }

public:
    int rob(vector<int>& nums) {
        // Implementation will be added here
        return 0;
    }
};
