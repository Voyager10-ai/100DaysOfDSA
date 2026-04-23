#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
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
    return 0;
}
