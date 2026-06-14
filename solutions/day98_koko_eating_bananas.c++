#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// LeetCode 875 – Koko Eating Bananas
//
// Koko loves to eat bananas. There are n piles of bananas, the i-th pile has piles[i] bananas.
// The guards have gone and will come back in h hours.
//
// Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile
// of bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats
// all of them instead and will not eat any more bananas during this hour.
//
// Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.
//
// Return the minimum integer k such that she can eat all the bananas within h hours.
//
// Example 1:
//   Input: piles = [3,6,7,11], h = 8
//   Output: 4
//
// Example 2:
//   Input: piles = [30,11,23,4,20], h = 5
//   Output: 30
//
// Example 3:
//   Input: piles = [30,11,23,4,20], h = 6
//   Output: 23

// Alternative approach: Linear Search (Naive approach)
// We try eating speed k starting from 1, and increment k until we find a speed that allows
// eating all bananas in <= h hours.
// Time Complexity: O(max(piles) * N) where N is piles.size().
// Space Complexity: O(1)
class SolutionAlt {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int max_pile = 0;
        for (int p : piles) {
            max_pile = max(max_pile, p);
        }
        
        for (int k = 1; k <= max_pile; ++k) {
            long long hours_needed = 0;
            for (int p : piles) {
                // Ceiling division: (p + k - 1) / k
                hours_needed += (static_cast<long long>(p) + k - 1) / k;
            }
            if (hours_needed <= h) {
                return k;
            }
        }
        return max_pile;
    }
};

// Optimal approach: Binary Search on the eating speed
// We know the speed k is in range [1, max(piles)].
// Since the hours needed monotonically decreases as k increases, we can perform binary search on k.
// Time Complexity: O(N * log(max(piles))) where N is piles.size().
// Space Complexity: O(1)
class Solution {
private:
    bool canEatAll(const vector<int>& piles, int h, int k) {
        long long hours = 0;
        for (int p : piles) {
            hours += (static_cast<long long>(p) + k - 1) / k; // ceil(p / k)
        }
        return hours <= h;
    }

public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int lo = 1;
        int hi = 0;
        for (int p : piles) {
            hi = max(hi, p);
        }
        
        int ans = hi;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (canEatAll(piles, h, mid)) {
                ans = mid;
                hi = mid - 1; // Try to find a smaller speed
            } else {
                lo = mid + 1; // Need a faster speed
            }
        }
        return ans;
    }
};

int testNum = 0;
void check(int gotOpt, int gotAlt, int expected, const string& desc) {
    ++testNum;
    bool passOpt = (gotOpt == expected);
    bool passAlt = (gotAlt == expected);
    bool pass = passOpt && passAlt;
    
    cout << "Test " << testNum << ": " << (pass ? "PASS" : "FAIL")
         << " - " << desc << endl;
    if (!passOpt) {
        cout << "  -> Optimal failed: got " << gotOpt << ", expected " << expected << endl;
    }
    if (!passAlt) {
        cout << "  -> Alt failed: got " << gotAlt << ", expected " << expected << endl;
    }
}

int main() {
    Solution solver;
    SolutionAlt solverAlt;
    
    // Test 1: Standard case (LeetCode Example 1)
    {
        vector<int> piles = {3, 6, 7, 11};
        int h = 8;
        check(solver.minEatingSpeed(piles, h), solverAlt.minEatingSpeed(piles, h), 4, "Example 1: piles=[3,6,7,11], h=8");
    }
    
    // Test 2: Standard case (LeetCode Example 2)
    {
        vector<int> piles = {30, 11, 23, 4, 20};
        int h = 5;
        check(solver.minEatingSpeed(piles, h), solverAlt.minEatingSpeed(piles, h), 30, "Example 2: piles=[30,11,23,4,20], h=5");
    }
    
    // Test 3: Standard case (LeetCode Example 3)
    {
        vector<int> piles = {30, 11, 23, 4, 20};
        int h = 6;
        check(solver.minEatingSpeed(piles, h), solverAlt.minEatingSpeed(piles, h), 23, "Example 3: piles=[30,11,23,4,20], h=6");
    }
    
    // Test 4: Single element, speed = 1
    {
        vector<int> piles = {30};
        int h = 30;
        check(solver.minEatingSpeed(piles, h), solverAlt.minEatingSpeed(piles, h), 1, "Single pile, h equals pile size: piles=[30], h=30");
    }
    
    // Test 5: Single element, speed > 1
    {
        vector<int> piles = {30};
        int h = 15;
        check(solver.minEatingSpeed(piles, h), solverAlt.minEatingSpeed(piles, h), 2, "Single pile, h half of pile size: piles=[30], h=15");
    }
    
    // Test 6: h equals total sum of piles, speed should be 1
    {
        vector<int> piles = {3, 6, 7, 11};
        int h = 27;
        check(solver.minEatingSpeed(piles, h), solverAlt.minEatingSpeed(piles, h), 1, "h equals sum of piles: piles=[3,6,7,11], h=27");
    }
    
    // Test 7: Large h compared to piles, speed should be 1
    {
        vector<int> piles = {3, 6, 7, 11};
        int h = 10000;
        check(solver.minEatingSpeed(piles, h), solverAlt.minEatingSpeed(piles, h), 1, "Large h: piles=[3,6,7,11], h=10000");
    }
    
    // Test 8: Large pile elements (within bounds for linear search to complete quickly)
    {
        vector<int> piles = {10000};
        int h = 5000;
        check(solver.minEatingSpeed(piles, h), solverAlt.minEatingSpeed(piles, h), 2, "Larger pile elements: piles=[10000], h=5000");
    }
    
    return 0;
}



