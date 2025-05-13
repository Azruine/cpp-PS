#include <vector>
#include <algorithm>

class Solution {
public:
    int lengthAfterTransformations(std::string s, int t) {
        constexpr int32_t MOD = 1'000'000'007;
        std::vector<int32_t> alpha(26, 0);
        std::vector<int32_t> new_alpha(26, 0);
        for (auto& c : s) {
            alpha[c - 'a']++;
        }
        int32_t big_T = t / 26;
        t %= 26;
        while (big_T--) {
            for (size_t i = 1; i < 27; i++) {
                new_alpha[i % 26] = (alpha[i % 26] + alpha[(i - 1) % 26]) % MOD;
            }
            new_alpha[1] = (new_alpha[1] + alpha[25]) % MOD;
            std::swap(alpha, new_alpha);
            std::ranges::fill(alpha, 0);
        }
        while (t--) {
            for (size_t i = 1; i < 27; i++) {
                new_alpha[i % 26] = alpha[i - 1];
            }
            new_alpha[1] = (new_alpha[1] + alpha[25]) % MOD;
            std::swap(alpha, new_alpha);
            std::ranges::fill(alpha, 0);
        }
        int32_t ret{0};
        for (auto& i : alpha) {
            ret = (ret + i) % MOD;
        }
        return ret;
    }
};
