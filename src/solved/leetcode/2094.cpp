/*==== Copyright 2025 Azruine ====*/

#include <utility>
#include <vector>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
const int32_t TEN = 10;
const int32_t HUNDRED = 100;
}  // namespace

class Solution {
public:
    std::vector<int32_t> findEvenNumbers(std::vector<int32_t>& digits) {
        std::vector<int32_t> result;
        std::vector<int32_t> count(TEN, 0);
        for (const auto& digit : digits) {
            count[as<size_t>(digit)]++;
        }

        for (size_t i = 1; i < TEN; i++) {
            if (count[i] > 0) {
                count[i]--;
                for (size_t j = 0; j < TEN; j++) {
                    if (count[j] > 0) {
                        count[j]--;
                        for (size_t k = 0; k < TEN; k++) {
                            if (count[k] > 0 && (k % 2 == 0)) {
                                result.push_back(
                                    as<int32_t>((i * HUNDRED) + (j * TEN) + k));
                            }
                        }
                        count[j]++;
                    }
                }
                count[i]++;
            }
        }

        return result;
    }
};
