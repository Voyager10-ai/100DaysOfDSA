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
    // Time Complexity: O(N) where N is the number of nodes in the BST.
    // Space Complexity: O(H) where H is the height of the BST due to recursion stack.
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

int main() {
    // Example 1: a valid BST
    //      2
    //     / \
    //    1   3
    TreeNode* root1 = new TreeNode(2);
    root1->left = new TreeNode(1);
    root1->right = new TreeNode(3);

    Solution sol;
    cout << "Example 1 isValidBST: " << (sol.isValidBST(root1) ? "true" : "false") << endl;

    // Example 2: an invalid BST
    //      5
    //     / \
    //    1   4
    //       / \
    //      3   6
    TreeNode* root2 = new TreeNode(5);
    root2->left = new TreeNode(1);
    root2->right = new TreeNode(4);
    root2->right->left = new TreeNode(3);
    root2->right->right = new TreeNode(6);

    cout << "Example 2 isValidBST: " << (sol.isValidBST(root2) ? "true" : "false") << endl;

    return 0;
}
