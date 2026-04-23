#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Time Complexity: O(N) where N is number of tasks, since we iterate through the list of tasks to count frequencies
    // Space Complexity: O(1) since the frequency array is always size 26
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> counts(26, 0);
        int maxFreq = 0;
        
        for (char task : tasks) {
            counts[task - 'A']++;
            maxFreq = max(maxFreq, counts[task - 'A']);
        }
        
        int maxFreqCount = 0;
        for (int count : counts) {
            if (count == maxFreq) {
                maxFreqCount++;
            }
        }
        
        int intervals = (maxFreq - 1) * (n + 1) + maxFreqCount;
        return max((int)tasks.size(), intervals);
    }
};

int main() {
    Solution sol;
    cout << "Testing Task Scheduler" << endl;
    
    vector<char> tasks1 = {'A', 'A', 'A', 'B', 'B', 'B'};
    int n1 = 2;
    cout << "Test 1 - Least Interval: " << sol.leastInterval(tasks1, n1) << " (Expected: 8)" << endl;

    vector<char> tasks2 = {'A', 'A', 'A', 'B', 'B', 'B'};
    int n2 = 0;
    cout << "Test 2 - Least Interval: " << sol.leastInterval(tasks2, n2) << " (Expected: 6)" << endl;

    vector<char> tasks3 = {'A', 'A', 'A', 'A', 'A', 'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    int n3 = 2;
    cout << "Test 3 - Least Interval: " << sol.leastInterval(tasks3, n3) << " (Expected: 16)" << endl;

    return 0;
}
