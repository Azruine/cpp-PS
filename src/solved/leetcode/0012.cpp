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

#include <string>

class Solution {
    std::string convert_digit(int32_t digit, int32_t pow) {
        std::string ret;
        static constexpr std::array<std::string_view, 3> romans = {
            "IVX",
            "XLC",
            "CDM",
        };
        if (pow < 0 || pow >= 3) {
            std::unreachable();
        }
        auto roman = romans[pow];
        if (digit == 0) {
        } else if (digit < 4) {
            ret = std::string(digit, roman[0]);
        } else if (digit == 4) {
            ret = std::string{roman[0], roman[1]};
        } else if (digit < 9) {
            ret = std::string{roman[1]} + std::string(digit - 5, roman[0]);
        } else {
            ret = std::string{roman[0], roman[2]};
        }
        return ret;
    }

public:
    std::string intToRoman(int num) {
        std::string ret;
        for (int32_t i = 0; i < 3; i++) {
            ret = convert_digit(num % 10, i) + ret;
            num /= 10;
        }
        // input limited to 3999
        ret = std::string(num % 10, 'M') + ret;
        return ret;
    }
};
