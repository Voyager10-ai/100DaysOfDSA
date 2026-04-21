#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/**
 * Day 56: Find Median from Data Stream
 * Problem Link: https://leetcode.com/problems/find-median-from-data-stream/
 * 
 * Approach:
 * We use two heaps to maintain the data stream:
 * 1. A max-heap to store the smaller half of the numbers.
 * 2. A min-heap to store the larger half of the numbers.
 * 
 * The size of the max-heap (small) is always equal to or one greater than the size of the min-heap (large).
 * This ensures that the median can be easily calculated from the tops of the heaps.
 */

class MedianFinder {
private:
    priority_queue<int> small; // max-heap
    priority_queue<int, vector<int>, greater<int>> large; // min-heap

public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        small.push(num);
        
        // Ensure every num in small is <= every num in large
        if (!small.empty() && !large.empty() && small.top() > large.top()) {
            int val = small.top();
            small.pop();
            large.push(val);
        }
        
        // Handle uneven size
        if (small.size() > large.size() + 1) {
            int val = small.top();
            small.pop();
            large.push(val);
        }
        if (large.size() > small.size() + 1) {
            int val = large.top();
            large.pop();
            small.push(val);
        }
    }
    
    double findMedian() {
        if (small.size() > large.size()) {
            return (double)small.top();
        } else if (large.size() > small.size()) {
            return (double)large.top();
        }
        return (small.top() + large.top()) / 2.0;
    }
};

int main() {
    MedianFinder* obj = new MedianFinder();
    obj->addNum(1);
    obj->addNum(2);
    cout << "Median: " << obj->findMedian() << endl; // Expected: 1.5
    obj->addNum(3);
    cout << "Median: " << obj->findMedian() << endl; // Expected: 2.0
    return 0;
}
