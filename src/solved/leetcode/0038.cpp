/*==== Copyright 2025 Azruine ====*/

#include <string>

class Solution {
public:
    std::string countAndSay(int n) {
        if (n == 1) {
            return "1";
        }
        std::string prev = countAndSay(n -1);
        std::string ret;
        size_t len = prev.length();
        size_t i = 0;
        while (i < len) {
            char cur = prev[i];
            int cnt = 0;
            while (i < len && prev[i] == cur) {
                i++;
                cnt++;
            }
            ret += std::to_string(cnt);
            ret.push_back(cur);
        }
        return ret;
    }
};

int main() {
    Solution sol;
    sol.countAndSay(4);
    return 0;
}
