#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define fastio                             \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class Solution {
public:
    int minOperations(std::vector<std::vector<int>>& grid, int x) {
        std::vector<int> flat;
        for (auto& v : grid) flat.insert(flat.end(), v.begin(), v.end());
        int n = flat.size();
        auto median = flat.begin() + flat.size() / 2;
        std::nth_element(flat.begin(), median, flat.end());
        int cnt = 0, r = flat.front() % x, m = flat[flat.size() / 2];
        for (auto& i : flat) {
            if (i % x != r) return -1;
            cnt += std::abs(m - i) / x;
        }
        return cnt;
    }
};