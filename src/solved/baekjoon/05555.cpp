#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

using std::cin, std::cout, std::endl;

#define fastio                             \
    std::ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                         \
    cout.tie(NULL);

class Solver {
private:
    std::string target;
    int n;
    std::vector<std::string> words;
    bool isContain(std::string const& s, std::string const& t) const {
        int len = s.length(), tlen = t.length();
        if (len < tlen) return false;
        for (int i = 0; i < len; ++i) {
            if (s[i] == t[0]) {
                int j = 1;
                while (j < tlen && s[(i + j) % len] == t[j]) {
                    ++j;
                }
                if (j == tlen) return true;
            }
        }
        return false;
    }

public:
    Solver() {}
    ~Solver() {}
    void solve() {
        std::cin >> target >> n;
        words.resize(n);
        for (auto& s : words) std::cin >> s;
        int cnt = 0;
        std::for_each(words.begin(), words.end(), [&](std::string const& s) {
            if (isContain(s, target)) cnt++;
        });
        cout << cnt;
    }
};

int main() {
    fastio;
    Solver solver;
    solver.solve();
    return 0;
}