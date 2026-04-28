#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    void backtrack(vector<int>& candidates, int target, int start, vector<int>& current, vector<vector<int>>& result) {
        if (target == 0) {
            result.push_back(current);
            return;
        }
        for (int i = start; i < candidates.size(); ++i) {
            if (i > start && candidates[i] == candidates[i - 1]) continue; // Skip duplicates
            if (candidates[i] > target) break; // Optimization
            
            current.push_back(candidates[i]);
            backtrack(candidates, target - candidates[i], i + 1, current, result);
            current.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> current;
        sort(candidates.begin(), candidates.end());
        backtrack(candidates, target, 0, current, result);
        return result;
    }
};

int main() {
    Solution sol;
    vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
    int target = 8;
    
    vector<vector<int>> result = sol.combinationSum2(candidates, target);
    
    for (const auto& comb : result) {
        cout << "[";
        for (int i = 0; i < comb.size(); ++i) {
            cout << comb[i] << (i == comb.size() - 1 ? "" : ", ");
        }
        cout << "]\n";
    }
    
    return 0;
}
