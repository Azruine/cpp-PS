#include <bits/stdc++.h>

class Solution
{
private:
    std::unordered_map<int, std::vector<int>> map;
    int getDigitSum(int x)
    {
        int ret = 0;
        while (x)
        {
            ret += x % 10;
            x /= 10;
        }
        return ret;
    }

public:
    int maximumSum(std::vector<int> &nums)
    {
        int n = static_cast<int>(nums.size());
        for (int i = 0; i < n; i++)
            map[getDigitSum(nums[i])].push_back(nums[i]);
        int ret = -1;
        for (auto &[_i, vec] : map)
        {
            if (static_cast<int>(vec.size()) < 2)
                continue;
            std::sort(vec.begin(), vec.end(), std::greater<int>());
            ret = std::max(ret, vec[0] + vec[1]);
        }
        return ret;
    }
};

int main()
{
    std::vector<int> test = {229,398,269,317,420,464,491,218,439,153,482,169,411,93,147,50,347,210,251,366,401};
    Solution sol;
    std::cout << sol.maximumSum(test);
    return 0;
}