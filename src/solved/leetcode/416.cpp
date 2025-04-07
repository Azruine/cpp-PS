#include <algorithm>
#include <limits>
#include <numeric>
#include <ranges>
#include <vector>

using std::vector;
constexpr int INT_MIN = std::numeric_limits<int32_t>::min();

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        if (sum & 1 || *std::max_element(nums.begin(), nums.end()) > (sum >> 1))
            return false;
        vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, 0));
        dp[0][0] = true;
        for (int i : std::views::iota(1, n + 1)) {
            for (int s : std::views::iota(0, sum + 1)) {
                dp[i][s] = dp[i - 1][s];
                if (s >= nums[i - 1]) dp[i][s] = dp[i][s] || dp[i - 1][s - nums[i - 1]];
            }
        }
        if (dp[n][sum / 2])
            return true;
        else
            return false;
    }
};