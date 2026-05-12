#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0) {
            return false;
        }
        
        int target = sum / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true;
        
        for (int num : nums) {
            for (int j = target; j >= num; --j) {
                dp[j] = dp[j] || dp[j - num];
            }
        }
        
        return dp[target];
    }
};

int main() {
    Solution sol;
    vector<int> nums1 = {1, 5, 11, 5};
    vector<int> nums2 = {1, 2, 3, 5};
    
    cout << "Test case 1: " << (sol.canPartition(nums1) ? "True" : "False") << " (Expected: True)" << endl;
    cout << "Test case 2: " << (sol.canPartition(nums2) ? "True" : "False") << " (Expected: False)" << endl;
    
    return 0;
}
