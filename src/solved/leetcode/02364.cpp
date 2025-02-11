#include <bits/stdc++.h>

class Solution
{
public:
    long long countBadPairs(std::vector<int> &nums)
    {
        long long n = static_cast<long long>(nums.size());
        std::unordered_map<long long, long long> map;
        for (long long i = 0; i < n; i++)
        {
            map[nums[i] - i]++;
        }
        long long sum = 0, ans = 0;
        for (auto &p : map)
        {
            ans += p.second * (sum - p.second);
            sum += p.second;
        }
        return ans;
    }
};