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

int main() {
    // Example usage:
    // Create the BST:
    //        6
    //      /   \
    //     2     8
    //    / \   / \
    //   0   4 7   9
    //      / \
    //     3   5
    
    TreeNode* root = new TreeNode(6);
    root->left = new TreeNode(2);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(4);
    root->left->right->left = new TreeNode(3);
    root->left->right->right = new TreeNode(5);
    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(9);
    
    Solution sol;
    
    // Example 1: LCA of 2 and 8 is 6
    TreeNode* p1 = root->left;   // Node 2
    TreeNode* q1 = root->right;  // Node 8
    TreeNode* lca1 = sol.lowestCommonAncestor(root, p1, q1);
    cout << "Lowest Common Ancestor of " << p1->val << " and " << q1->val 
         << " is: " << (lca1 ? lca1->val : -1) << endl;
         
    // Example 2: LCA of 2 and 4 is 2
    TreeNode* p2 = root->left;         // Node 2
    TreeNode* q2 = root->left->right;  // Node 4
    TreeNode* lca2 = sol.lowestCommonAncestor(root, p2, q2);
    cout << "Lowest Common Ancestor of " << p2->val << " and " << q2->val 
         << " is: " << (lca2 ? lca2->val : -1) << endl;
    
    return 0;
}
