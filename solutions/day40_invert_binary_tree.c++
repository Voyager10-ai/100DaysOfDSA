#include <iostream>
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
 * Day 40: Invert Binary Tree
 *
 * Approach:
 * Using a recursive approach (DFS) to invert the tree.
 * At every node, we swap its left and right children, then
 * recursively invert the left and right subtrees.
 * The base case is a null node — we simply return nullptr.
 *
 * Time Complexity:  O(N) — every node is visited exactly once.
 * Space Complexity: O(H) — recursion stack uses height of tree; O(log N) average, O(N) worst case.
 */
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) return nullptr;

        TreeNode* tmp = root->left;
        root->left = root->right;
        root->right = tmp;

        invertTree(root->left);
        invertTree(root->right);

        return root;
    }
};

int main() {
    Solution sol;

    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(9);

    TreeNode* result = sol.invertTree(root);

    // Clean up
    delete root->left->left; delete root->left->right;
    delete root->right->left; delete root->right->right;
    delete root->left; delete root->right;
    delete root;

    return 0;
}
