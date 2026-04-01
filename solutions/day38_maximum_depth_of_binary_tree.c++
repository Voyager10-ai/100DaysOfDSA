#include <iostream>
#include <algorithm>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*
 * Day 38: Maximum Depth of Binary Tree
 * 
 * Approach:
 * Using a recursive approach to find the maximum depth of the binary tree.
 * The depth of a node is 1 + the maximum depth of its left and right subtrees.
 * The base case is when the tree is empty (root is nullptr), its depth is 0.
 * Time Complexity: O(N) where N is the number of nodes in the tree.
 * Space Complexity: O(H) where H is the height of the tree (for the recursion stack).
 */
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int leftDepth = maxDepth(root->left);
        int rightDepth = maxDepth(root->right);
        return max(leftDepth, rightDepth) + 1;
    }
};

int main() {
    Solution sol;
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    cout << sol.maxDepth(root) << endl;
    
    // Clean up memory
    delete root->right->right;
    delete root->right->left;
    delete root->right;
    delete root->left;
    delete root;
    return 0;
}
