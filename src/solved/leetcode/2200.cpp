/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <cstdint>
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
    std::vector<int32_t> findKDistantIndices(std::vector<int32_t>& nums,
                                             int32_t key, int32_t k) {
        std::vector<int32_t> res;
        for (auto i{0}; i < as<int32_t>(nums.size()); i++) {
            if (nums[as<size_t>(i)] == key) {
                for (int32_t j{std::max<int32_t>(0, i - k)};
                     j <= std::min<int32_t>(
                              static_cast<int32_t>(nums.size() - 1), i + k);
                     j++) {
                    res.push_back(j);
                }
            }
        }
        std::ranges::sort(res);
        res.erase(std::unique(res.begin(), res.end()), res.end());
        return res;
    }
};
