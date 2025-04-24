/*==== Copyright 2025 Azruine ====*/

#include <cstdint>
#include <functional>
#include <algorithm>
#include <vector>

class Solution {
public:
    static int32_t getXORSum(std::vector<int32_t>& arr1,
                             std::vector<int32_t>& arr2) {
        return std::ranges::fold_left(arr1, 0, std::bit_xor{}) &
               std::ranges::fold_left(arr2, 0, std::bit_xor{});
    }
};

int main() {
    std::vector<int> arr1{1, 2, 3};
    std::vector<int> arr2{1, 2, 3};
    return Solution::getXORSum(arr1, arr2);
}
