/*==== Copyright 2025 Azruine ====*/

#include <cstdint>
#include <string>
#include <utility>
#include <bitset>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

class Solution {
public:
    int32_t longestSubsequence(std::string s, int32_t k) {
        std::string k_str = std::bitset<32>(k).to_string();
        while (cmp(s, k_str)) {
            s.erase(s.find_first_of('1'), 1);
        }
        return static_cast<int32_t>(s.size());
    }

private:
    bool cmp(std::string const& lhs, std::string const& rhs) const {
        auto lhs_first_it = lhs.find_first_of('1');
        auto rhs_first_it = rhs.find_first_of('1');
        if (lhs_first_it == std::string::npos ||
            rhs_first_it == std::string::npos) {
            return lhs_first_it != std::string::npos;
        }
        auto lhs_right_idx = lhs.length() - lhs_first_it - 1;
        auto rhs_right_idx = rhs.length() - rhs_first_it - 1;
        if (lhs_right_idx != rhs_right_idx) {
            return lhs_right_idx > rhs_right_idx;
        }
        for (size_t i = 0; i < lhs_right_idx; ++i) {
            if (lhs[lhs_first_it + i] != rhs[rhs_first_it + i]) {
                return lhs[lhs_first_it + i] > rhs[rhs_first_it + i];
            }
        }
        return false;
    }
};
