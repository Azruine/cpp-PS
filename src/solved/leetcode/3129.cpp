/*==== Copyright 2025 Azruine ====*/

#include <ranges>
#include <utility>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
struct Range {
    template <typename Sentinel>
    constexpr auto operator()(Sentinel sentinel) const noexcept {
        return std::views::iota(static_cast<Sentinel>(0), sentinel);
    }
    template <typename Start, typename Sentinel>
    constexpr auto operator()(Start start, Sentinel sentinel) const noexcept {
        return std::views::iota(start, sentinel);
    }
    template <typename Start, typename Sentinel, typename Step>
    constexpr auto operator()(Start start, Sentinel sentinel,
                              Step step) const noexcept {
        return std::views::iota(start, sentinel) | std::views::stride(step);
    }
};
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
constexpr Range _iota{};
#pragma GCC diagnostic pop
}  // namespace

#include <array>

class Solution {
    constexpr static int32_t MOD = 1'000'000'007;
    constexpr static size_t MAX = 1'010;
    std::array<std::array<std::array<int64_t, 2>, MAX>, MAX> dp;

public:
    int numberOfStableArrays(int zero, int one, int limit) {
        for (size_t i = 0; i <= zero; i++) {
            for (size_t j = 0; j <= one; j++) {
                for (auto last : {0UL, 1UL}) {
                    if (i == 0) {
                        dp[i][j][last] = (last == 1 && j <= limit);
                    } else if (j == 0) {
                        dp[i][j][last] = (last == 0 && i <= limit);
                    } else if (last == 0) {
                        dp[i][j][last] = dp[i - 1][j][0] + dp[i - 1][j][1];
                        if (i > limit) {
                            dp[i][j][last] -= dp[i - limit - 1][j][1];
                        }
                    } else if (last == 1) {
                        dp[i][j][last] = dp[i][j - 1][0] + dp[i][j - 1][1];
                        if (j > limit) {
                            dp[i][j][last] -= dp[i][j - limit - 1][0];
                        }
                    }
                    dp[i][j][last] = (dp[i][j][last] % MOD + MOD) % MOD;
                }
            }
        }
        return (dp[zero][one][0] + dp[zero][one][1]) % MOD;
    }
};
