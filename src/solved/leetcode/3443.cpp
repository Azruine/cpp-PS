/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <stdexcept>
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
    int maxDistance(std::string s, int k) {
        auto n{s.length()};
        auto x{0}, y{0};
        auto res{0};
        for (size_t i{0}; i < n; i++) {
            switch (s[i]) {
                case 'E':
                    x++;
                    break;
                case 'S':
                    y--;
                    break;
                case 'W':
                    x--;
                    break;
                case 'N':
                    y++;
                    break;
                default:
                    throw std::invalid_argument("Invalid character in string");
            }
            res = std::max(res, std::min(std::abs(x) + std::abs(y) + (k * 2),
                                         as<int32_t>(i + 1)));
        }
        return res;
    }
};
