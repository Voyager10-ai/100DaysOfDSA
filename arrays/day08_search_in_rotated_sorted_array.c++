#include <vector>

using namespace std;

class Solution {
public:
    // O(log n) time complexity, O(1) space complexity
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] == target) {
                return mid;
            }
            
            // Check if the left half is sorted
            if (nums[left] <= nums[mid]) {
                // Target is in the sorted left half
                if (target >= nums[left] && target < nums[mid]) {
                    right = mid - 1;
                } 
                // Target is in the right half
                else {
                    left = mid + 1;
                }
            } 
            // Otherwise, the right half must be sorted
            else {
                // Target is in the sorted right half
                if (target > nums[mid] && target <= nums[right]) {
                    left = mid + 1;
                } 
                // Target is in the left half
                else {
                    right = mid - 1;
                }
            }
        }
        
        return -1; // Target not found
    }
};
