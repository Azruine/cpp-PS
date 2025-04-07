#include <bits/stdc++.h>

class Solution {
public:
    std::vector<int> applyOperations(std::vector<int> &nums) {
        int n = static_cast<int>(nums.size());
        for (int i = 1; i < n; i++) {
            if (nums[i - 1] == nums[i]) {
                nums[i - 1] <<= 1;
                nums[i] = 0;
            }
        }
        std::vector<int> ret;
        int cnt = 0;
        for (auto &i : nums) {
            if (i == 0)
                cnt++;
            else
                ret.emplace_back(i);
        }
        while (cnt--) ret.emplace_back(0);
        return ret;
    }
};