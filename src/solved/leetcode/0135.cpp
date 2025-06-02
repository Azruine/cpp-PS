/*==== Copyright 2025 Azruine ====*/

#include <numeric>
#include <utility>
#include <vector>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

class Solution {
public:
    int32_t candy(std::vector<int32_t>& ratings) {
        size_t n{ratings.size()};
        std::vector<int32_t> candies(n, 1);
        for (size_t i{1}; i < n; ++i) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }
        for (size_t i{n - 1}; i > 0; --i) {
            if (ratings[i - 1] > ratings[i]) {
                candies[i - 1] = std::max(candies[i - 1], candies[i] + 1);
            }
        }
        return std::accumulate(candies.begin(), candies.end(), 0);
    }
};
