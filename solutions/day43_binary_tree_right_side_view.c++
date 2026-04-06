#include <iostream>
#include <vector>
#include <queue>

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

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        return result;
    }
};

int main() {
    Solution sol;
    
    // Create a sample tree
    //     1
    //    / \
    //   2   3
    //    \   \
    //     5   4
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(4);
    
    vector<int> res = sol.rightSideView(root);
    for (int val : res) {
        cout << val << " ";
    }
    cout << endl;
    
    // Clean up
    delete root->right->right;
    delete root->left->right;
    delete root->right;
    delete root->left;
    delete root;
    
    return 0;
}
