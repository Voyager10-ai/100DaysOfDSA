#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // O(n) time complexity, O(1) space complexity
    int maxArea(vector<int>& height) {
        int max_water = 0;
        int left = 0;
        int right = height.size() - 1;
        
        while (left < right) {
            // Calculate the area using the shorter line
            int current_width = right - left;
            int current_height = min(height[left], height[right]);
            int current_area = current_width * current_height;
            
            // Update the maximum water found so far
            max_water = max(max_water, current_area);
            
            // Move the pointer pointing to the shorter line inward
            // since moving the taller line can't possibly increase the area
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        
        return max_water;
    }
};
