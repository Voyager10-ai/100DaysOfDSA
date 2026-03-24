#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // O(n) time complexity, O(1) space complexity
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return;
        
        // Step 1: Find the first decreasing element from the end
        int i = n - 2;
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            i--;
        }
        
        // Step 2: If such an element is found, find the element just larger than it from the end
        if (i >= 0) {
            int j = n - 1;
            while (j >= 0 && nums[j] <= nums[i]) {
                j--;
            }
            // Swap the two elements
            swap(nums[i], nums[j]);
        }
        
        // Step 3: Reverse the elements from i + 1 to the end to get the smallest lexicographical order
        reverse(nums.begin() + i + 1, nums.end());
    }
};
