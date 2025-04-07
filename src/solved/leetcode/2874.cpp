#include <cstdint>
#include <limits>
#include <numeric>
#include <ranges>
#include <vector>

using std::vector;

class Solution {
public:
    long long maximumTripletValue(vector<int>& nums) {
        long long ans = 0;
        int n = nums.size();
        int left_max = nums[0];

        std::vector<int> right_max(n);
        right_max[n - 1] = nums[n - 1];
        for (int i = n - 2; i > 0; i--)
            right_max[i] = std::max(right_max[i + 1], nums[i]);

        for (int i : std::views::iota(1, n - 1)) {
            ans = std::max(
                static_cast<int64_t>(ans),
                static_cast<int64_t>(left_max - nums[i]) * right_max[i + 1]);
            left_max = std::max(left_max, nums[i]);
        }
        return ans;
    }
};