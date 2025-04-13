/*==== Copyright 2025 Azruine ====*/

#include <cstdint>

class Solution {
private:
    constexpr static int EVEN = 4;
    constexpr static int ODD = 5;
    constexpr static int MOD = 1'000'000'007;

public:
    static int64_t pow(int64_t base, int64_t exp) {
        base %= MOD;
        int64_t res = 1;
        while (exp > 0) {
            if ((exp & 1) == 1) {
                res = (res * base) % MOD;
            }
            exp >>= 1;
            base = (base * base) % MOD;
        }
        return res % MOD;
    }
    int countGoodNumbers(int64_t n) {
        int64_t odd = (n + 1) / 2;
        int64_t even = n / 2;
        int64_t ans = pow(EVEN, even);
        ans = (ans * pow(ODD, odd)) % MOD;
        return static_cast<int>(ans);
    }
};
