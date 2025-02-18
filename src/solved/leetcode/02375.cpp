#include <bits/stdc++.h>
class Solution
{
public:
    std::string smallestNumber(std::string pattern)
    {
        int len = pattern.length();
        std::vector<std::pair<int, int>> D;
        bool isD = false;
        int s = 0, e = 0;
        for (int i = 0; i < len; i++)
        {
            if (!isD && pattern[i] == 'D')
            {
                isD = true;
                s = i;
            }
            else if (isD && pattern[i] != 'D')
            {
                D.push_back({s, i - 1});
                isD = false;
            }
        }
        if (isD)
            D.push_back({s, len - 1});
        std::vector<int> set;
        for (int i = 0; i <= len; i++)
            set.emplace_back(i + 1);
        for (auto [s, e] : D)
            std::reverse(set.begin() + s, set.begin() + e + 2);
        int num = 0;
        for (auto &i : set)
        {
            num *= 10;
            num += i;
        }
        return std::to_string(num);
    }
};