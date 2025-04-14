/*==== Copyright 2025 Azruine ====*/

#include <print>
#include <ranges>
#include <vector>

class Solution {
public:
    int countGoodTriplets(std::vector<int>& arr, int a, int b, int c) {
        size_t n = arr.size();
        int32_t cnt = 0;
        for (auto k : std::views::iota(size_t{0}, n)) {
            for (auto j : std::views::iota(size_t{0}, k)) {
                if (std::abs(arr.at(j) - arr.at(k)) > b) {
                    continue;
                }
                for (auto i : std::views::iota(size_t{0}, j)) {
                    if (std::abs(arr.at(i) - arr.at(j)) <= a &&
                        std::abs(arr.at(k) - arr.at(i)) <= c) {
                        cnt++;
                    }
                }
            }
        }
        return cnt;
    }
};
