#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    int maxPathDown(TreeNode* node, int& maxValue) {
        if (node == NULL) return 0;
        
        int left = max(0, maxPathDown(node->left, maxValue));
        int right = max(0, maxPathDown(node->right, maxValue));
        
        maxValue = max(maxValue, left + right + node->val);
        
        return max(left, right) + node->val;
    }
    
public:
    int maxPathSum(TreeNode* root) {
        int maxValue = INT_MIN;
        maxPathDown(root, maxValue);
        return maxValue;
    }
};

int main() {
    Solution sol;
    
    // Example 1
    //   1
    //  / \
    // 2   3
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    
    cout << "Max path sum 1: " << sol.maxPathSum(root1) << endl; // Output: 6
    
    // Example 2
    //   -10
    //   / \
    //  9  20
    //    /  \
    //   15   7
    TreeNode* root2 = new TreeNode(-10);
    root2->left = new TreeNode(9);
    root2->right = new TreeNode(20);
    root2->right->left = new TreeNode(15);
    root2->right->right = new TreeNode(7);
    
    cout << "Max path sum 2: " << sol.maxPathSum(root2) << endl; // Output: 42
    
    return 0;
}
