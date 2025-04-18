/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <cstdint>
#include <limits>
#include <ranges>
#include <utility>
#include <vector>

class Solution {
public:
    int mctFromLeafValues(std::vector<int>& arr) {
        int ans = 0;
        while (arr.size() > 1) {
            trans(arr, ans);
        }
        return ans;
    }
    static void trans(std::vector<int>& arr, int& ans) {
        std::vector<int> temp;
        size_t n = arr.size();
        temp.reserve(n);
        int min = std::numeric_limits<int32_t>::max();
        size_t min_idx = 0;
        for (size_t i : std::views::iota(size_t{0}, n - 1)) {
            if (arr[i] * arr[i + 1] < min) {
                min = arr[i] * arr[i + 1];
                min_idx = i;
            }
        }
        for (size_t i = 0; i < n; i++) {
            if (i != min_idx) {
                temp.push_back(arr[i]);
            } else {
                temp.push_back(std::max(arr[i], arr[i + 1]));
                ans += arr[i] * arr[i + 1];
                i += 1;
            }
        }
        arr.clear();
        arr = std::move(temp);
    }
};
