#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    TreeNode* build(vector<int>& preorder, int preStart, int preEnd, 
                    vector<int>& inorder, int inStart, int inEnd, 
                    unordered_map<int, int>& inMap) {
        if (preStart > preEnd || inStart > inEnd) {
            return NULL;
        }
        
        TreeNode* root = new TreeNode(preorder[preStart]);
        
        int inRootIndex = inMap[root->val];
        int numsLeft = inRootIndex - inStart;
        
        root->left = build(preorder, preStart + 1, preStart + numsLeft, 
                           inorder, inStart, inRootIndex - 1, inMap);
        root->right = build(preorder, preStart + numsLeft + 1, preEnd, 
                            inorder, inRootIndex + 1, inEnd, inMap);
                            
        return root;
    }

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> inMap;
        for (int i = 0; i < inorder.size(); ++i) {
            inMap[inorder[i]] = i;
        }
        
        return build(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1, inMap);
    }
};
