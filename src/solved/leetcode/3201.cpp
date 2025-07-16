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
    int32_t maximumLength(std::vector<int32_t>& nums) {
        int32_t c1, c2, c3, c4;
        c1 = c2 = c3 = c4 = 0;
        for (auto const& num : nums) {
            if (num & 1) {
                c1 += 1;
                c3 = std::max(c3, c4 + 1);
            } else {
                c2 += 1;
                c4 = std::max(c4, c3 + 1);
            }
        }
        return std::ranges::max({c1, c2, c3, c4});
    }
};
