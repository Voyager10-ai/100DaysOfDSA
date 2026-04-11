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
private:
    int count = 0;
    int result = 0;

    void inOrder(TreeNode* node, int k) {
        if (!node || count >= k) return;
        
        inOrder(node->left, k);
        
        count++;
        if (count == k) {
            result = node->val;
            return;
        }
        
        inOrder(node->right, k);
    }
    
public:
    // Time Complexity: O(H + k) where H is tree height
    // Space Complexity: O(H) for recursion stack
    int kthSmallest(TreeNode* root, int k) {
        inOrder(root, k);
        return result;
    }
};

int main() {
    // Example 1
    //      3
    //     / \
    //    1   4
    //     \
    //      2
    TreeNode* root1 = new TreeNode(3);
    root1->left = new TreeNode(1);
    root1->right = new TreeNode(4);
    root1->left->right = new TreeNode(2);

    Solution sol;
    cout << "1st smallest element: " << sol.kthSmallest(root1, 1) << endl;

    // We shouldn't reuse the same Solution object if it holds state (count, result)
    // So create a new instance for test 2
    // Example 2
    //       5
    //      / \
    //     3   6
    //    / \
    //   2   4
    //  /
    // 1
    TreeNode* root2 = new TreeNode(5);
    root2->left = new TreeNode(3);
    root2->right = new TreeNode(6);
    root2->left->left = new TreeNode(2);
    root2->left->right = new TreeNode(4);
    root2->left->left->left = new TreeNode(1);

    Solution sol2;
    cout << "3rd smallest element: " << sol2.kthSmallest(root2, 3) << endl;

    return 0;
}
