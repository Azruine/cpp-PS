/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <vector>

class Solution {
public:
    int32_t maximumLength(std::vector<int32_t>& nums, int32_t k_) {
        auto k = static_cast<size_t>(k_);
        int32_t ret = 0;
        std::vector<size_t> data(k, 0);
        for (size_t sum = 0; sum < k; sum++) {
            std::ranges::fill(data, 0);
            data[static_cast<size_t>(nums[0]) % k] = 1;
            for (auto _i = 1U; _i < nums.size(); _i++) {
                auto i = static_cast<size_t>(nums[_i]) % k;
                auto prev = (k + sum - i) % k;
                data[i] = data[prev] + 1;
                ret = std::max(ret, static_cast<int32_t>(data[i]));
            }
        }
        return ret;
    }

private:
};
