/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <cctype>
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
    bool isValid(std::string word) {
        if (word.size() < 3) {
            return false;
        }
        bool consonant = false;
        bool vowel = false;
        std::ranges::transform(word, word.begin(), [](unsigned char chr) {
            return std::tolower(chr);
        });
        for (auto chr : word) {
            if (vowels.find(chr) != std::string_view::npos) {
                vowel = true;
            } else if (consonants.find(chr) != std::string_view::npos) {
                consonant = true;
            } else if (digits.find(chr) == std::string_view::npos) {
                return false;
            }
        }
        return consonant && vowel;
    }

private:
    static constexpr std::string_view vowels = "aeiou";
    static constexpr std::string_view consonants = "bcdfghjklmnpqrstvwxyz";
    static constexpr std::string_view digits = "0123456789";
};
