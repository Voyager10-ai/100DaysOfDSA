#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    // O(n) time, O(1) space
    int maxProduct(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        int result = nums[0];
        int max_so_far = nums[0];
        int min_so_far = nums[0];
        
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < 0) {
                swap(max_so_far, min_so_far);
            }
            
            max_so_far = max(nums[i], max_so_far * nums[i]);
            min_so_far = min(nums[i], min_so_far * nums[i]);
            
            result = max(result, max_so_far);
        }
        
        return result;
    }
};

