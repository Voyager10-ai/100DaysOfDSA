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

/*day 
 * Day 39: Same Tree
 * 
 * Approach:
 * Using a recursive approach to perform a simultaneous traversal of both trees.
 * - If both nodes are null, they are identical up to this point.
 * - If only one node is null, or if their values differ, they are not identical.
 * - If their values match, recursively check the left subtree and the right subtree.
 * 
 * Time Complexity: O(min(N, M)) where N and M are the number of nodes in trees p and q respectively.
 * Space Complexity: O(min(H1, H2)) where H1 and H2 are the heights of the trees, due to recursion stack.
 */
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == nullptr && q == nullptr) return true;
        if (p == nullptr || q == nullptr) return false;
        if (p->val != q->val) return false;
        
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
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
