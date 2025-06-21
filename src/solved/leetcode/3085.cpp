/*==== Copyright 2025 Azruine ====*/

#include <array>
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
    int32_t minimumDeletions(std::string word, int32_t k) {
        for (char chr : word) {
            char_count.at(as<size_t>(chr - 'a'))++;
        }
        int32_t ret{std::numeric_limits<int32_t>::max()};
        for (auto const& min_freq : char_count) {
            int32_t local_min{0};
            if (min_freq == 0) {
                continue;
            }
            for (auto const& freq : char_count) {
                if (freq < min_freq) {
                    local_min += freq;
                } else if (freq > min_freq + k) {
                    local_min += freq - (min_freq + k);
                }
            }
            ret = std::min(ret, local_min);
        }
        return ret;
    }

private:
    constexpr static size_t ALPHABET_SIZE = 26;
    std::array<int32_t, ALPHABET_SIZE> char_count{0};
};
