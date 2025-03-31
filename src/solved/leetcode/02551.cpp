#include <algorithm>
#include <ranges>
#include <vector>

class Solution {
public:
    long long putMarbles(std::vector<int>& weights, int k) {
        if (!(--k)) return 0;
        std::vector<int> endPairs;
        int n = static_cast<int>(weights.size()) - 1;
        for (int i : std::views::iota(0, n))
            endPairs.emplace_back(weights[i] + weights[i + 1]);
        long long ans = 0;
        std::nth_element(endPairs.begin(), endPairs.begin() + k,
                         endPairs.end());
        for (int i : std::views::iota(0, k)) ans -= endPairs[i];
        std::nth_element(endPairs.begin(), endPairs.end() - k, endPairs.end());
        for (int i : std::views::iota(0, k)) ans += endPairs[n - i - 1];
        return ans;
    }
};