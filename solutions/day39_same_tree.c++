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

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        return false;
    }
};

int main() {
    Solution sol;
    
    TreeNode* p = new TreeNode(1);
    p->left = new TreeNode(2);
    p->right = new TreeNode(3);
    
    TreeNode* q = new TreeNode(1);
    q->left = new TreeNode(2);
    q->right = new TreeNode(3);
    
    if (sol.isSameTree(p, q)) {
        cout << "Trees are the same" << endl;
    } else {
        cout << "Trees are different" << endl;
    }
    
    // Clean up
    delete p->left; delete p->right; delete p;
    delete q->left; delete q->right; delete q;
    
    return 0;
}
