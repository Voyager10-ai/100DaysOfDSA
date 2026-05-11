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

int main() {
    Solution solution;
    
    vector<int> nums1 = {2, 3, -2, 4};
    cout << "Test 1: " << (solution.maxProduct(nums1) == 6 ? "Pass" : "Fail") << endl;
    
    vector<int> nums2 = {-2, 0, -1};
    cout << "Test 2: " << (solution.maxProduct(nums2) == 0 ? "Pass" : "Fail") << endl;
    
    vector<int> nums3 = {-2, 3, -4};
    cout << "Test 3: " << (solution.maxProduct(nums3) == 24 ? "Pass" : "Fail") << endl;
    
    return 0;
}
