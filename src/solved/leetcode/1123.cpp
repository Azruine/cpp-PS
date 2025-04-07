#include <functional>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        std::function<std::pair<TreeNode*, int>(TreeNode*)> getLCA =
            [&](TreeNode* a) -> std::pair<TreeNode*, int> {
            if (a == nullptr) return {nullptr, -1};

            auto [left, left_depth] = getLCA(a->left);
            auto [right, right_depth] = getLCA(a->right);

            if (left_depth == right_depth) {
                return {a, left_depth + 1};
            } else if (left_depth > right_depth) {
                return {left, left_depth + 1};
            } else {
                return {right, right_depth + 1};
            }
        };
        auto [lca, _] = getLCA(root);
        return lca;
    }
};