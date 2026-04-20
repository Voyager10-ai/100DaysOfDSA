#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // Use a min-heap to keep track of the k largest elements
        priority_queue<int, vector<int>, greater<int>> minHeap;
        
        for (int num : nums) {
            minHeap.push(num);
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }
        
        // The top of the heap is the kth largest element
        return minHeap.top();
    }
};

int main() {
    Solution sol;
    vector<int> nums1 = {3, 2, 1, 5, 6, 4};
    int k1 = 2;
    cout << "Kth largest in {3, 2, 1, 5, 6, 4} with k=2: " << sol.findKthLargest(nums1, k1) << " (Expected: 5)" << endl;

    vector<int> nums2 = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    int k2 = 4;
    cout << "Kth largest in {3, 2, 3, 1, 2, 4, 5, 5, 6} with k=4: " << sol.findKthLargest(nums2, k2) << " (Expected: 4)" << endl;

    return 0;
}
