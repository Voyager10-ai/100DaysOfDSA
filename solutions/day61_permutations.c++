#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    void backtrack(vector<int>& nums, vector<vector<int>>& res, vector<int>& current, vector<bool>& used) {
        if (current.size() == nums.size()) {
            res.push_back(current);
            return;
        }
        
        for (int i = 0; i < nums.size(); ++i) {
            if (!used[i]) {
                used[i] = true;
                current.push_back(nums[i]);
                backtrack(nums, res, current, used);
                current.pop_back();
                used[i] = false;
            }
        }
    }

public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> current;
        vector<bool> used(nums.size(), false);
        backtrack(nums, res, current, used);
        return res;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> res = sol.permute(nums);
    
    cout << "Permutations:" << endl;
    for (const auto& p : res) {
        cout << "[ ";
        for (int num : p) {
            cout << num << " ";
        }
        cout << "]" << endl;
    }
    
    return 0;
}
