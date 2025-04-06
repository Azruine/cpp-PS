#include <algorithm>
#include <ranges>
#include <vector>

using std::vector;

class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        // first = last index, second = length;
        vector<std::pair<int, int>> dp(n, {-1, 0});
        dp[0] = {-1, 0};
        vector<int> ans;
        int max_idx = 0;
        for (int i : std::views::iota(1, n)) {
            for (int j : std::views::iota(0, i)) {
                if (nums[i] % nums[j] == 0 && dp[i].second < dp[j].second + 1) {
                    dp[i] = {j, dp[j].second + 1};
                }
            }
            if (dp[i].second > dp[max_idx].second) {
                max_idx = i;
            }
        }
        int idx = max_idx;
        while (idx != -1) {
            ans.emplace_back(nums[idx]);
            idx = dp[idx].first;
        }
        return ans;
    }
};

int main() {
    vector<int> p = {1, 2, 3};
    Solution sol;
    sol.largestDivisibleSubset(p);
    return 0;
}