/*==== Copyright 2025 Azruine ====*/

#include <functional>
#include <ranges>
#include <unordered_map>
#include <utility>
#include <vector>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

template <typename T>
using ordered_set_less =
    __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>,
                     __gnu_pbds::rb_tree_tag,
                     __gnu_pbds::tree_order_statistics_node_update>;

template <typename T>
using ordered_set_greater =
    __gnu_pbds::tree<T, __gnu_pbds::null_type, std::greater<T>,
                     __gnu_pbds::rb_tree_tag,
                     __gnu_pbds::tree_order_statistics_node_update>;

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

class Solution {
public:
    int64_t goodTriplets(std::vector<int>& nums1, std::vector<int>& nums2) {
        size_t n = nums1.size();
        ordered_set_less<size_t> small;
        ordered_set_greater<size_t> big(nums1.begin(), nums1.end());
        std::vector<size_t> indices(n, 0);
        std::unordered_map<size_t, size_t> indices_map;
        for (auto i : std::views::iota(size_t{0}, n)) {
            indices_map[as<size_t>(nums2[i])] = i;
        }
        uint64_t ans = 0;
        for (auto i : std::views::iota(size_t{0}, n)) {
            small.insert(indices_map[as<size_t>(nums1[i])]);
            ans += (small.order_of_key(indices_map[as<size_t>(nums1[i])]) *
                    big.order_of_key(indices_map[as<size_t>(nums1[i])]));
            big.erase(indices_map[as<size_t>(nums1[i])]);
        }
        return as<int64_t>(ans);
    }
};
