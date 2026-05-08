#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) return 0;
        if (nums.size() == 1) return nums[0];
        
        int prev1 = 0;
        int prev2 = 0;
        
        for (int num : nums) {
            int current = max(prev1, prev2 + num);
            prev2 = prev1;
            prev1 = current;
        }
        
        return prev1;
    }
};

int main() {
    Solution solution;
    
    vector<int> nums1 = {1, 2, 3, 1};
    cout << "Test 1: " << (solution.rob(nums1) == 4 ? "Pass" : "Fail") << endl;
    
    vector<int> nums2 = {2, 7, 9, 3, 1};
    cout << "Test 2: " << (solution.rob(nums2) == 12 ? "Pass" : "Fail") << endl;

    vector<int> nums3 = {0};
    cout << "Test 3: " << (solution.rob(nums3) == 0 ? "Pass" : "Fail") << endl;
    
    return 0;
}
