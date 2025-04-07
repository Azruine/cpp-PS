#include <bits/stdc++.h>

class Solution {
public:
    int minCapability(std::vector<int> &nums, int k) {
        int n = static_cast<int>(nums.size());
        int l = 1, r = 1'000'000'001, cnt = 0;
        while (l < r) {
            cnt = 0;
            int mid = (l + r) / 2;
            bool prev = false;
            for (auto &i : nums) {
                if (!prev && i <= mid) {
                    prev = !prev;
                    cnt++;
                } else if (prev) {
                    prev = !prev;
                }
            }
            if (cnt >= k)
                r = mid;
            else
                l = mid + 1;
        }
        return l;
    }
};