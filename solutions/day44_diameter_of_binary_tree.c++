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
 * Day 44: Diameter of Binary Tree
 *
 * Approach:
 * We use a recursive Depth First Search (DFS) or post-order traversal to calculate the
 * height of each node. During the traversal, the diameter passing through a node is simply
 * the sum of the maximum heights of its left and right subtrees.
 * We maintain a global or member variable to track the maximum diameter found so far.
 *
 * Time Complexity:  O(N) — since we visit every node exactly once.
 * Space Complexity: O(H) — due to the recurrence stack, where H is the height of the tree.
 */
class Solution {
public:
    int diameter = 0;
    
    int height(TreeNode* node) {
        if (node == nullptr) return 0;
        
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        
        diameter = max(diameter, leftHeight + rightHeight);
        
        return 1 + max(leftHeight, rightHeight);
    }
    
    int diameterOfBinaryTree(TreeNode* root) {
        diameter = 0;
        height(root);
        return diameter;
    }
};

int main() {
    Solution sol;
    
    // Create a sample tree
    //     1
    //    / \
    //   2   3
    //  / \
    // 4   5
    
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    
    cout << "Diameter: " << sol.diameterOfBinaryTree(root) << endl;
    
    // Clean up
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right;
    delete root;
    
    return 0;
}
