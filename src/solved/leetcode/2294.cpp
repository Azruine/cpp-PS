/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <bitset>
#include <limits>
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
    int partitionArray(std::vector<int>& nums, int k) {
        std::bitset<100001> bitset;
        auto min = std::numeric_limits<int>::max();
        auto max = std::numeric_limits<int>::min();
        for (auto& num : nums) {
            bitset.set(as<size_t>(num));
            min = std::min(min, num);
            max = std::max(max, num);
        }
        int cnt = 0;
        int cur = min;
        while (cur <= max) {
            if (!bitset.test(as<size_t>(cur))) {
                cur++;
                continue;
            }
            cnt++;
            cur += k + 1;
            while (cur <= max && !bitset.test(as<size_t>(cur))) {
                cur++;
            }
        }
        return cnt;
    }
};
