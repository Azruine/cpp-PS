/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <ranges>
#include <utility>
#include <vector>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

class Solution {
private:
    static constexpr auto MAX = 37;
    static constexpr auto TEN = 10;

public:
    int countLargestGroup(int n) {
        std::vector<int> m_(MAX, 0);
        for (auto i : std::views::iota(1, n + 1)) {
            auto sum = 0;
            while (i > 0) {
                sum += i % TEN;
                i /= TEN;
            }
            m_[as<size_t>(sum)]++;
        }
        auto max = 0;
        for (auto i : m_) {
            max = std::max(max, i);
        }
        auto count = 0;
        for (auto i : m_) {
            if (i == max) {
                count++;
            }
        }
        return count;
    }
};
