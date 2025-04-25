/*==== Copyright 2025 Azruine ====*/

#include <numeric>
#include <ranges>
#include <unordered_map>
#include <vector>

class Solution {
public:
    int64_t countInterestingSubarrays(std::vector<int32_t>& nums,
                                      int32_t modulo, int32_t k) {
        for (auto& i : nums) {
            i %= modulo;
        }
        std::vector<int32_t> prefix(nums.size() + 1, 0);
        prefix.front() = 0;
        std::inclusive_scan(
            nums.begin(), nums.end(), std::next(prefix.begin(), 1),
            [&](int32_t acc, int32_t x) { return (acc + (x == k)) % modulo; }, 0);
        std::unordered_map<int32_t, int32_t> bucket;
        int64_t ans{0};
        bucket[0]++;
        for (auto i : std::views::iota(size_t{1}, nums.size() + 1)) {
            ans += bucket[(prefix[i] + modulo - k) % modulo];
            bucket[prefix[i]]++;
        }
        return ans;
    }
};
