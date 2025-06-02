/*==== Copyright 2025 Azruine ====*/

#include <limits>
#include <utility>
#include <vector>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
using value_it =
    std::pair<std::vector<int32_t>::iterator, std::vector<int32_t>::iterator>;
}  // namespace

class Solution {
public:
    int64_t maxSpending(std::vector<std::vector<int32_t>>& values) {
        size_t n = values.size();
        size_t m = values[0].size();
        int64_t ret{0};
        for (int64_t i = 0; i < as<int64_t>(m * n); i++) {
            int32_t min_value{std::numeric_limits<int32_t>::max()};
            size_t min_index{0};
            for (size_t j = 0; j < n; j++) {
                if (!values[j].empty() && values[j].back() < min_value) {
                    min_value = values[j].back();
                    min_index = j;
                }
            }
            ret += (i + 1) * as<int64_t>(min_value);
            values[min_index].pop_back();
        }
        return ret;
    }
};
