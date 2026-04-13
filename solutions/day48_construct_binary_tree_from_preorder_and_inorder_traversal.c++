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

void printInorder(TreeNode* node) {
    if (node == NULL) return;
    printInorder(node->left);
    cout << node->val << " ";
    printInorder(node->right);
}

int main() {
    Solution sol;
    
    // Example 1
    vector<int> preorder1 = {3, 9, 20, 15, 7};
    vector<int> inorder1 = {9, 3, 15, 20, 7};
    TreeNode* root1 = sol.buildTree(preorder1, inorder1);
    cout << "Inorder of constructed tree 1: ";
    printInorder(root1); // Output should be 9 3 15 20 7
    cout << endl;
    
    // Example 2
    vector<int> preorder2 = {-1};
    vector<int> inorder2 = {-1};
    TreeNode* root2 = sol.buildTree(preorder2, inorder2);
    cout << "Inorder of constructed tree 2: ";
    printInorder(root2); // Output should be -1
    cout << endl;
    
    return 0;
}
