#include <vector>

using namespace std;

class Solution {
public:
    // O(n) time complexity, O(1) space complexity
    // Floyd's Tortoise and Hare (Cycle Detection) approach
    int findDuplicate(vector<int>& nums) {
        // Find the intersection point of the two runners.
        int tortoise = nums[0];
        int hare = nums[0];
        
        do {
            tortoise = nums[tortoise];
            hare = nums[nums[hare]];
        } while (tortoise != hare);

        // Find the "entrance" to the cycle.
        tortoise = nums[0];
        while (tortoise != hare) {
            tortoise = nums[tortoise];
            hare = nums[hare];
        }

        return hare;
    }
};
