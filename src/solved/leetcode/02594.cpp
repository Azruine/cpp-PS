#include <bits/stdc++.h>

class Solution {
public:
    long long repairCars(std::vector<int> &ranks, int cars) {
        int maxRank = -1, minRank = 110;
        std::array<int, 101> freq = {0};
        for (auto &i : ranks) {
            maxRank = std::max(maxRank, i);
            minRank = std::min(minRank, i);
            freq[i]++;
        }
        long long l = 1, r = 1LL * minRank * cars * cars;
        while (l < r) {
            long long cnt = 0;
            long long mid = (l + r) / 2;
            for (int i = minRank; i <= maxRank; i++) {
                cnt += freq[i] * (long long)(std::sqrt(mid / i));
                if (cnt >= cars) break;
            }
            if (cnt < cars)
                l = mid + 1;
            else
                r = mid;
        }
        return l;
    }
};