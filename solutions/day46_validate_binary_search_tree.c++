#include <iostream>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return validate(root, nullptr, nullptr);
    }

private:
    bool validate(TreeNode* node, TreeNode* low, TreeNode* high) {
        if (!node) {
            return true;
        }
        
        // Check if current node violates the min/max constraint
        if ((low && node->val <= low->val) || (high && node->val >= high->val)) {
            return false;
        }
        
        // Validates left and right subtrees
        return validate(node->left, low, node) && 
               validate(node->right, node, high);
    }
};
