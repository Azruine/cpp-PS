/*==== Copyright 2025 Azruine ====*/

#include <bit>
#include <cstdint>
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
    char kthCharacter(int64_t k, std::vector<int32_t>& operations) {
        static constexpr int32_t ALPHA = 26;
        int32_t ret = 0;
        k -= 1;
        for (auto i = std::bit_width(as<size_t>(k)) - 1; i >= 0; i--) {
            if ((k & (1L << i)) && operations[as<size_t>(i)] == 1) {
                ret += 1;
            }
        }
        return as<char>(ret % ALPHA + 'a');
    }
};
