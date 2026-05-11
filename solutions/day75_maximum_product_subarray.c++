#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        int maxProd = nums[0];
        int minProd = nums[0];
        int result = nums[0];
        
        for (int i = 1; i < nums.size(); ++i) {
            int num = nums[i];
            int tempMax = max({num, maxProd * num, minProd * num});
            minProd = min({num, maxProd * num, minProd * num});
            maxProd = tempMax;
            
            result = max(result, maxProd);
        }
        
        return result;
    }
};
