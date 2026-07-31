/*==== Copyright 2025 Azruine ====*/

#include <ranges>
#include <utility>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
struct Range {
    template <typename Sentinel>
    constexpr auto operator()(Sentinel sentinel) const noexcept {
        return std::views::iota(static_cast<Sentinel>(0), sentinel);
    }
    template <typename Start, typename Sentinel>
    constexpr auto operator()(Start start, Sentinel sentinel) const noexcept {
        return std::views::iota(start, sentinel);
    }
    template <typename Start, typename Sentinel, typename Step>
    constexpr auto operator()(Start start, Sentinel sentinel,
                              Step step) const noexcept {
        return std::views::iota(start, sentinel) | std::views::stride(step);
    }
};
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
constexpr Range _iota{};
#pragma GCC diagnostic pop
}  // namespace

#include <vector>

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
    std::vector<int> inorderTraversal(TreeNode* root) {
        std::vector<int32_t> ret;
        // node, expanded
        std::vector<std::pair<TreeNode*, bool>> stk;
        if (root) {
            stk.emplace_back(root, false);
        }
        while (!stk.empty()) {
            auto [cur_node, is_expanded] = stk.back();
            stk.pop_back();
            if (is_expanded) {
                ret.emplace_back(cur_node->val);
                continue;
            }
            // reversed push
            if (cur_node->right != nullptr) {
                stk.emplace_back(cur_node->right, false);
            }
            stk.emplace_back(cur_node, true);
            if (cur_node->left != nullptr) {
                stk.emplace_back(cur_node->left, false);
            }
        }
        return ret;
    }
};
