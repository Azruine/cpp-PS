/*==== Copyright 2025 Azruine ====*/

#include <utility>
#include <string>
#include <vector>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

class Solution {
public:
    std::vector<std::string> getLongestSubsequence(std::vector<std::string>& words,
                                         std::vector<int>& groups) {
        std::vector<std::string> ret_0;
        std::vector<std::string> ret_1;
        int cur_0{0};
        size_t n{words.size()};
        for (size_t i = 0; i < n; i++) {
            if (groups[i] == cur_0) {
                cur_0 = 1 - cur_0;
                ret_0.push_back(words[i]);
            }
        }
        int cur_1{0};
        for (size_t i = 0; i < n; i++) {
            if (groups[i] == cur_1) {
                cur_1 = 1 - cur_1;
                ret_1.push_back(words[i]);
            }
        }
        return (ret_0.size() > ret_1.size() ? ret_0 : ret_1);
    }
};
