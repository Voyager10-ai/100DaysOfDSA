#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/*
 * Day 37: Largest Rectangle in Histogram
 * 
 * Approach:
 * Using a monotonic increasing stack to store pairs of {index, height}.
 * When we encounter a building with a height smaller than the top of the stack,
 * we can no longer extend the rectangle of the top building. So we pop it,
 * calculate its area, and continue. The width of the rectangle is determined
 * by the difference between the current index and the index of the popped building.
 * We also update the index of the current building to the index of the LAST
 * popped building since the current building can extend backwards.
 */
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
