/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <ranges>
#include <utility>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
struct Range {
    template <typename Start, typename End, typename Step = Start>
    constexpr auto operator()(Start start, End end,
                              Step step = 1) const noexcept {
        return std::views::iota(start, end) | std::views::stride(step);
    }
};
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
constexpr Range iota{};
#pragma GCC diagnostic pop
}  // namespace

class Solution {
private:
    int32_t removing(std::string& str, std::string const& key, int32_t x) {
        int32_t ret = 0;
        size_t idx = 0;
        for (auto i : iota(0U, str.size())) {
            auto chr = str[i];
            if (idx > 0 && str[idx - 1] == key[0] && chr == key[1]) {
                idx--;
                ret += x;
            } else {
                str[idx++] = chr;
            }
        }
        str.resize(idx);
        return ret;
    }

public:
    int32_t maximumGain(std::string str, int32_t x, int32_t y) {
        std::string key = "ab";
        if (y > x) {
            std::swap(x, y);
            key = "ba";
        }
        int32_t ret = 0;
        ret += removing(str, key, x);
        std::ranges::reverse(key);
        ret += removing(str, key, y);
        return ret;
    }
};
