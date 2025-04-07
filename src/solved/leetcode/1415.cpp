#include <bits/stdc++.h>
class Solution {
private:
    std::string back(std::string cur, int n, int k, int &cnt)
    {
        int len = cur.length();
        static std::array<char, 3> charr = {'a', 'b', 'c'};
        if (len == n && ++cnt == k) {
            return cur;
        } else if (len == n && cnt < k) {
            return "";
        }
        for (auto &c : charr) {
            if (len != 0 && cur.back() == c)
                continue;
            cur += c;
            std::string ret = back(cur, n, k, cnt);
            if (ret != "")
                return ret;
            cur.pop_back();
        }
        return "";
    }
public:
    std::string getHappyString(int n, int k) {
        int cnt = 0;
        return back("", n, k, cnt);
    }
};