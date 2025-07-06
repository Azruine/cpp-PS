/*==== Copyright 2025 Azruine ====*/

#include <array>
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
    int32_t findLucky(std::vector<int32_t>& arr) {
        constexpr static size_t MAX = 501;
        std::array<size_t, MAX> freq = {};
        for (auto& i : arr) {
            freq[as<size_t>(i)]++;
        }
        int32_t ans = -1;
        for (size_t i = 1; i < MAX; i++) {
            if (freq[i] == i) {
                ans = as<int32_t>(i);
            }
        }
        return ans;
    }
};
