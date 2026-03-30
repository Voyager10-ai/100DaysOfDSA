#include <vector>
#include <iostream>

#include <stack>

using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> answer(n, 0);
        stack<int> s; 

        for (int i = 0; i < n; i++) {
            while (!s.empty() && temperatures[s.top()] < temperatures[i]) {
                int prevIndex = s.top();
                s.pop();
                answer[prevIndex] = i - prevIndex;
            }
            s.push(i);
        }
        return answer;
    }
};
