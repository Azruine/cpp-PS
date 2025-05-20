/*==== Copyright 2025 Azruine ====*/

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
    bool isZeroArray(std::vector<int32_t>& nums,
                     std::vector<std::vector<int32_t>>& queries) {
        std::vector<int32_t> diff(nums.size() + 1, 0);
        for (auto& query : queries) {
            diff[as<size_t>(query.front())]++;
            diff[as<size_t>(query.back()) + 1]--;
        }
        int32_t sum{0};
        bool res = true;
        for (size_t i = 0; i < nums.size(); i++) {
            sum += diff[i];
            if (sum < nums[i]) {
                res = false;
                break;
            }
        }
        return res;
    }
};
