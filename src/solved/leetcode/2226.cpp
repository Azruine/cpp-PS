#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define fastio                             \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class Solution {
private:
    bool isPossible(std::vector<int> &v, long long k, int div) {
        return k <= std::accumulate(v.begin(), v.end(), 0LL,
                                    [&](long long acc, long long x) {
                                        return acc + (x / div);
                                    });
    }

public:
    int maximumCandies(std::vector<int> &candies, long long k) {
        long long total = std::accumulate(candies.begin(), candies.end(), 0LL);
        if (k > total)
            return 0;
        else if (k == total)
            return 1;
        long long l = 2, r = total / k + 1;
        while (l < r) {
            long long mid = (l + r) / 2;
            if (isPossible(candies, k, mid))
                l = mid + 1;
            else
                r = mid;
        }
        return l - 1;
    }
};