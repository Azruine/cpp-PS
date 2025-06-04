/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
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
    std::string answerString(std::string word, int32_t numFriends) {
        if (numFriends == 1) {
            return word;
        }
        size_t max_len = word.length() - as<size_t>(numFriends) + 1;
        char max_char = *std::ranges::max_element(word);
        std::vector<size_t> max_idx;
        for (size_t i = 0; i < word.length(); ++i) {
            if (word[i] == max_char) {
                max_idx.push_back(i);
            }
        }
        std::vector<std::string> substrings;
        for (auto& idx : max_idx) {
            size_t start = idx;
            size_t end = std::min(idx + max_len, word.length());
            substrings.push_back(word.substr(start, end - start));
        }
        return *std::ranges::max_element(substrings);
    }
};
