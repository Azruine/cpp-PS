/*==== Copyright 2025 Azruine ====*/

#include <cstdint>
#include <algorithm>
#include <vector>

class Solution {
public:
    int numberOfArrays(std::vector<int>& differences, int lower, int upper) {
        int64_t max{0};
        int64_t min{0};
        int64_t cur{0};
        for (auto& i : differences) {
            cur += i;
            max = std::max(max, cur);
            min = std::min(min, cur);
        }
        int64_t ans = upper - lower + 1;
        int64_t range = max - min + 1;
        return static_cast<int32_t>(std::max(int64_t{0}, ans - range + 1));
    }
};
