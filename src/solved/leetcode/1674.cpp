/*==== Copyright 2025 Azruine ====*/

#include <numeric>
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
#include <vector>

class Solution {
public:
    int32_t minMoves(std::vector<int32_t>& nums, int32_t limit) {
        auto n = nums.size();
        std::vector<int32_t> diff((limit << 1) + 3, 0);
        std::vector<int32_t> prefix((limit << 1) + 4, 0);
        for (auto i = 0UL; i < (n >> 1); i++) {
            auto sum = nums[i] + nums[n - i - 1];
            auto lower = std::min(nums[i], nums[n - i - 1]) + 1;
            auto upper = std::max(nums[i], nums[n - i - 1]) + limit;
            diff[sum] += 1;
            diff[sum + 1] -= 1;
            diff[lower] += 1;
            diff[upper + 1] -= 1;
        }
        std::inclusive_scan(diff.begin(), diff.end(), prefix.begin(),
                            std::plus<>());
        return n - std::ranges::max(prefix);
    }
};

int main() {
    Solution sol;
    std::vector<int32_t> arr = {1, 2, 4, 3};
    return sol.minMoves(arr, 4);
}
