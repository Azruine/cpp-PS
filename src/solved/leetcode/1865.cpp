/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <cstdint>
#include <unordered_map>
#include <utility>
#include <vector>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

class FindSumPairs {
public:
    FindSumPairs(std::vector<int32_t>& num1, std::vector<int32_t>& num2)
        : nums1(num1), nums2(num2) {
        for (auto& i : nums2) {
            cache2[i]++;
        }
    }

    void add(int32_t index, int32_t val) {
        auto& target = nums2[as<size_t>(index)];
        cache2[target]--;
        if (cache2[target] == 0) {
            cache2.erase(target);
        }
        target += val;
        cache2[target]++;
    }

    int32_t count(int32_t tot) {
        int32_t ret = 0;
        for (auto& i : nums1) {
            if (cache2.contains(tot - i)) {
                ret += cache2[tot - i];
            }
        }
        return ret;
    }

private:
    std::vector<int32_t>& nums1, nums2;
    std::unordered_map<int32_t, int32_t> cache2;
};
