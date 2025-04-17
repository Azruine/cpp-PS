/*==== Copyright 2025 Azruine ====*/

#include <cstdint>
#include <ranges>
#include <utility>
#include <vector>

using ll = int64_t;
using ull = uint64_t;
using ld = long double;

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

class Solution {
public:
    int countPairs(std::vector<int>& nums, int k) {
        int cnt = 0;
        size_t n = nums.size();
        for (size_t i : std::views::iota(size_t{0}, n)) {
            for (size_t j : std::views::iota(i + 1, n)) {
                if (nums[i] == nums[j] && (i * j) % as<size_t>(k) == 0) {
                    cnt++;
                }
            }
        }
        return cnt;
    }
};
