/*==== Copyright 2025 Azruine ====*/

#include <cstdint>
#include <string>
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
    std::vector<std::string> divideString(std::string s, size_t k, char fill) {
        std::vector<std::string> result;
        for (size_t i{0}; i < s.size(); i++) {
            if (i % k == 0) {
                result.emplace_back();
            }
            result.back().push_back(s[i]);
        }
        result.back().append(
            as<std::string>(std::string(k - result.back().size(), fill)));
        return result;
    }
};
