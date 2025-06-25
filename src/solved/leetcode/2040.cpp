/*==== Copyright 2025 Azruine ====*/

#include <cstdint>
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
    int64_t kthSmallestProduct(std::vector<int32_t>& nums1,
                               std::vector<int32_t>& nums2, int64_t k) {
        auto m = as<int64_t>(nums2.size());
        left = -1e10, right = 1e10;
        while (left < right) {
            mid = left + (right - left) / 2;
            int64_t count = 0;
            for (auto num1 : nums1) {
                if (num1 == 0) {
                    count += (mid >= 0) ? m : 0;
                    continue;
                }
                int32_t low = 0, high = as<int32_t>(m);
                while (low < high) {
                    int32_t mid2 = (low + high) / 2;
                    int64_t product =
                        as<int64_t>(num1) * nums2[as<size_t>(mid2)];
                    if (product <= mid) {
                        if (num1 > 0) {
                            low = mid2 + 1;
                        } else {
                            high = mid2;
                        }
                    } else {
                        if (num1 > 0) {
                            high = mid2;
                        } else {
                            low = mid2 + 1;
                        }
                    }
                }
                count += (num1 > 0) ? low : (m - low);
            }
            if (count < k) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }

private:
    int64_t left{0}, right{0}, mid{0};
};
