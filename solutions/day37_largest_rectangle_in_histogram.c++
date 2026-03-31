#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int maxArea = 0;
        stack<pair<int, int>> st; // pair: <index, height>
        
        for (int i = 0; i < heights.size(); i++) {
            int start = i;
            while (!st.empty() && st.top().second > heights[i]) {
                pair<int, int> topPop = st.top();
                st.pop();
                maxArea = max(maxArea, topPop.second * (i - topPop.first));
                start = topPop.first;
            }
            st.push({start, heights[i]});
        }
        
        while (!st.empty()) {
            pair<int, int> topPop = st.top();
            st.pop();
            int n = heights.size();
            maxArea = max(maxArea, topPop.second * (n - topPop.first));
        }
        
        return maxArea;
    }
};

int main() {
    Solution sol;
    vector<int> heights = {2,1,5,6,2,3};
    cout << sol.largestRectangleArea(heights) << endl;
    return 0;
}
