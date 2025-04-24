/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <cstdint>
#include <unordered_set>
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
    int32_t countCompleteSubarrays(std::vector<int32_t>& nums) {
        size_t len{nums.size()};
        size_t total_cnt{std::unordered_set(nums.begin(), nums.end()).size()};
        size_t max{as<size_t>(*std::ranges::max_element(nums))};

        size_t sub_cnt{0};
        size_t left{0};
        size_t right{0};
        int32_t ans{0};

        std::vector<int> freq(max + 1, 0);

        while (right < len) {
            auto cur{nums.at(right++)};
            if (freq.at(as<size_t>(cur))++ == 0) {
                sub_cnt++;
            }
            while (total_cnt == sub_cnt) {
                ans += as<int32_t>(len - right + 1);
                auto to_delete{nums.at(left++)};
                if (--freq.at(as<size_t>(to_delete)) == 0) {
                    sub_cnt--;
                }
            }
        }
        return ans;
    }
};
