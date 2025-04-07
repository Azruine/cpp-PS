#include <algorithm>
#include <ranges>
#include <vector>

using std::vector;
using std::views::iota;

class Solution {
public:
    long long maximumTripletValue(vector<int>& nums) {
        int n = nums.size();
        long long ans = 0;
        for (int i : iota(0, n)) {
            for (int j : iota(i + 1, n)) {
                for (int k : iota(j + 1, n)) {
                    ans =
                        std::max(ans, ((long long)nums[i] - nums[j]) * nums[k]);
                }
            }
        }
        return ans;
    }
};