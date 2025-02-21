#include <bits/stdc++.h>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class FindElements {
private:
    TreeNode *root;
    void construct(TreeNode *curNode) {
        int curValue = curNode->val;
        TreeNode *left = curNode->left;
        if (left != nullptr) {
            left->val = (curValue << 1) + 1;
            construct(left);
        }
        TreeNode *right = curNode->right;
        if (right != nullptr) {
            right->val = (curValue << 1) + 2;
            construct(right);
        }
    }

public:
    FindElements(TreeNode *root) : root(root) {
        root->val = 1;
        construct(root);
    }

    bool find(int target) {
        if (target == 0) return true;
        target++;
        std::string s = "";
        while (target > 1) {
            s += (target & 1 ? "r" : "l");
            target >>= 1;
        }
        std::reverse(s.begin(), s.end());
        TreeNode *cur = root;
        for (auto &c : s) {
            if (cur == nullptr) return false;
            if (c == 'l') {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }
        return (cur != nullptr);
    }
};