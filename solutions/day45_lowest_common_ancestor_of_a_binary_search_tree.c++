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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return NULL;
        
        int curr = root->val;
        
        // If both p and q are greater than root, LCA must be in the right subtree
        if (p->val > curr && q->val > curr) {
            return lowestCommonAncestor(root->right, p, q);
        }
        // If both p and q are lesser than root, LCA must be in the left subtree
        else if (p->val < curr && q->val < curr) {
            return lowestCommonAncestor(root->left, p, q);
        }
        
        // We have found the split point, so this node is the LCA
        return root;
    }
};
