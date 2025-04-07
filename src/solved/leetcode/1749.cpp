#include <bits/stdc++.h>
class Solution {
public:
    int maxAbsoluteSum(std::vector<int> &nums) {
        int n = static_cast<int>(nums.size());
        int max = 0, min = 0, ans = 0;
        for (auto &i : nums) {
            max = std::max(i, i + max);
            min = std::min(i, i + min);
            ans = std::max(ans, std::max(std::abs(max), std::abs(min)));
        }
        return ans;
    }
};