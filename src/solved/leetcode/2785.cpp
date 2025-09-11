/*==== Copyright 2025 Azruine ====*/

#include <utility>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

#include <array>
#include <cstdint>
#include <string>

class Solution {
public:
    std::string sortVowels(std::string const& str) {
        std::array<uint32_t, 128> chrs = {};
        constexpr static __uint128_t ONE = 1;
        constexpr static __uint128_t MASK =
            (ONE << 'a') | (ONE << 'e') | (ONE << 'i') | (ONE << 'o') |
            (ONE << 'u') | (ONE << 'A') | (ONE << 'E') | (ONE << 'I') |
            (ONE << 'O') | (ONE << 'U');

        for (auto const& chr : str) {
            if ((ONE << chr) & MASK) {
                chrs[as<size_t>(chr)] += 1;
            }
        }

        size_t cur = 0;
        std::string ret;
        for (auto const& chr : str) {
            if ((ONE << chr) & MASK) {
                while (chrs[cur] == 0 && cur < 128) {
                    cur++;
                }
                ret.push_back(as<char>(cur));
                chrs[cur]--;
            } else {
                ret.push_back(chr);
            }
        }
        return ret;
    }
};
