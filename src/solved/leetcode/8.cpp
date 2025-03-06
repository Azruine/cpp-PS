#include <string>

class Solution {
public:
    int myAtoi(std::string s) {
        long long ans = 0;
        int l = s.length();
        bool sign = true;
        bool isReadingNum = false;
        long long upper = (long long)1 << 31;
        long long lower = (long long)1 << 31;
        upper--;
        lower *= -1;
        for (int i = 0; i < l; i++) {
            if (s[i] != ' ' && s[i] != '+' && s[i] != '-' && !isdigit(s[i]))
                break;
            if (!isdigit(s[i]) && isReadingNum) break;
            if (s[i] == ' ') continue;
            if (s[i] == '-') {
                sign = false;
                isReadingNum = true;
                continue;
            }
            if (s[i] == '+') {
                isReadingNum = true;
                continue;
            }
            if (isdigit(s[i]) && !isReadingNum) isReadingNum = true;
            if (isdigit(s[i])) {
                ans *= 10;
                ans += s[i] - '0';
            }
            if (ans < lower || ans > upper) break;
        }
        if (!sign) ans *= -1;
        if (ans < lower) ans = lower;
        if (ans > upper) ans = upper;
        return ans;
    }
};