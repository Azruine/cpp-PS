/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <utility>
#include <vector>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

class Solution {
public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        std::vector<std::vector<int>> ret;
        std::ranges::sort(nums);
        do {
            ret.push_back(nums);
        } while (std::ranges::next_permutation(nums).found);
        return ret;
    }
};
