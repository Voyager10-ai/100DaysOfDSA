#include <vector>

using namespace std;

class Solution {
public:
    // Binary Search - O(log n) time, O(1) space
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            // If the middle element is greater than the rightmost element,
            // the minimum must be to the right of mid.
            if (nums[mid] > nums[right]) {
                left = mid + 1;
            } 
            // Otherwise, the minimum must be at mid or to the left of mid.
            else {
                right = mid;
            }
        }
        
        return nums[left]; // left and right will converge to the minimum
    }
};
