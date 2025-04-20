/*==== Copyright 2025 Azruine ====*/

#include <array>
#include <cmath>
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
    static constexpr size_t MAX = 1001;
    std::array<size_t, MAX> rabbits{
        0,
    };

public:
    int numRabbits(std::vector<int>& answers) {
        for (auto& i : answers) {
            rabbits.at(as<size_t>(i))++;
        }
        size_t ans = 0;
        for (auto i : std::views::iota(size_t{0}, MAX)) {
            if (rabbits.at(i) == 0) {
                continue;
            }
            ans += ((rabbits.at(i) + i) / (i + 1)) * (i + 1);
        }
        return as<int32_t>(ans);
    }
};
