/*==== Copyright 2025 Azruine ====*/

#include <cstdint>
#include <limits>
#include <string>
#include <utility>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

class Solution {
public:
    int32_t maxDifference(std::string s, int32_t k) {
        auto GetStatus = [](int32_t const a, int32_t const b) -> int32_t {
            return (a & 1) << 1 | (b & 1);
        };
        auto n = s.size();
        int32_t ans{std::numeric_limits<int32_t>::min()};
        for (char a{'0'}; a <= '4'; a++) {
            for (char b{'0'}; b <= '4'; b++) {
                if (a == b) {
                    continue;
                }
                std::array<int32_t, 4> cnt{std::numeric_limits<int32_t>::max(),
                                           std::numeric_limits<int32_t>::max(),
                                           std::numeric_limits<int32_t>::max(),
                                           std::numeric_limits<int32_t>::max()};
                int32_t cnt_a{0}, cnt_b{0};
                int32_t prev_a{0}, prev_b{0};
                int32_t left{-1};
                for (int32_t right{0}; right < as<int32_t>(n); right++) {
                    cnt_a += (s[as<size_t>(right)] == a);
                    cnt_b += (s[as<size_t>(right)] == b);
                    while (right - left >= k && cnt_b - prev_b >= 2) {
                        int32_t left_status{GetStatus(prev_a, prev_b)};
                        cnt.at(left_status) =
                            std::min(cnt.at(left_status), prev_a - prev_b);
                        left += 1;
                        prev_a += (s[as<size_t>(left)] == a);
                        prev_b += (s[as<size_t>(left)] == b);
                    }
                    int32_t right_status{GetStatus(cnt_a, cnt_b)};
                    if (cnt.at(right_status ^ 0b10) !=
                        std::numeric_limits<int32_t>::max()) {
                        ans = std::max(
                            ans, cnt_a - cnt_b - cnt.at(right_status ^ 0b10));
                    }
                }
            }
        }
        return ans;
    }
};
