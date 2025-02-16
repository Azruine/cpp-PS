#include <bits/stdc++.h>

class Solution
{
public:
    bool backtrack(std::vector<int> &res, std::vector<int> &cnt, int depth, int n)
    {
        if (depth == res.size())
            return true;

        if (res[depth] != 0)
            return backtrack(res, cnt, depth + 1, n);
        for (int i = n; i >= 1; i--)
        {
            if (cnt[i] == 2 || (i == 1 && cnt[i] == 1))
                continue;
            res[depth] = i;
            cnt[i]++;
            if (i != 1 && depth + i < res.size() && res[depth + i] == 0)
            {
                res[depth + i] = i;
                cnt[i]++;
                if (backtrack(res, cnt, depth + 1, n))
                    return true;
                res[depth + i] = 0;
                cnt[i]--;
            }
            else if (i == 1)
            {
                if (backtrack(res, cnt, depth + 1, n))
                    return true;
            }
            res[depth] = 0;
            cnt[i]--;
        }
        return false;
    }
    std::vector<int> constructDistancedSequence(int n)
    {
        std::vector<int> res((n << 1) - 1);
        std::vector<int> cnt(n + 1);
        backtrack(res, cnt, 0, n);
        return res;
    }
};