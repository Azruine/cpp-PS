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

#include <algorithm>
#include <cstdint>
#include <numeric>
#include <vector>

class Solution {
    constexpr static uint32_t BITS = 15;
    constexpr static uint32_t MAX = 1U << BITS;

public:
    int64_t findKthSmallest(std::vector<int32_t>& coins, int32_t k) {
        size_t n = coins.size();
        std::ranges::sort(coins);
        std::vector<bool> is_excluded(n, false);
        for (size_t i = 0; i < n; i++) {
            if (is_excluded[i]) {
                continue;
            }
            for (size_t j = i + 1; j < n; j++) {
                if (is_excluded[j]) {
                    continue;
                }
                if (std::gcd(coins[i], coins[j]) == coins[i]) {
                    is_excluded[j] = true;
                }
                if (std::gcd(coins[i], coins[j]) == coins[j]) {
                    is_excluded[i] = true;
                }
            }
        }
        std::vector<int32_t> arr;
        for (size_t i = 0; i < n; i++) {
            if (!is_excluded[i]) {
                arr.emplace_back(coins[i]);
            }
        }
        n = arr.size();
        std::array<int64_t, MAX> lcms = {};
        for (uint32_t mask = 1U; mask < MAX; mask++) {
            int64_t lcm = 1;
            for (size_t i = 0; i < n; i++) {
                if ((mask >> i) & 1) {
                    lcm = std::lcm(lcm, arr[i]);
                }
            }
            lcms[mask] = lcm;
        }
        auto get_muls = [&](int64_t upper) {
            int64_t ret = 0;
            for (uint32_t mask = 1U; mask < 1U << n; mask++) {
                uint32_t cnt = std::popcount(mask);
                if (cnt & 1) {
                    ret += (upper / lcms[mask]);
                } else {
                    ret -= (upper / lcms[mask]);
                }
            }
            return ret;
        };
        int64_t left = 1;
        int64_t right = 1'000'000'000'000'000'000;
        while (left < right) {
            int64_t mid = left + ((right - left) >> 1);
            if (get_muls(mid) < k) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        while (left > 1 && get_muls(left - 1) == k) {
            left -= 1;
        }
        return left;
    }
};

/*
 * gcd(x, y) == x 면 y는 삭제
 * 이걸 해도 2^15 개 gcd lcm 관리하긴 해야됨
 * 만약 lcm이 겹치면?
 * pqr로 봤을때, 예를 들어 pppqrr pqqqr -> pppqqqrr 이랑 ppp qqqrr -> pppqqqrr
 * 로 겹친다. 근데 25까지라서 이런 일이 없나? 일단 단순하게 포함배제만 걸어보자
 * 1U -> (1U << 15) - 1U 까지 전부 다 돌린다. 대충 3만개.
 * 그러면 array에 저장해놓고, 저 range에 대해 포함배제 돌리면 될듯?
 */
