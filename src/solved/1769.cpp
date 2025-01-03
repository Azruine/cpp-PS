#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define fastio                             \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

std::istream &operator>>(std::istream &is, std::pair<int, int> &p)
{
    is >> p.first >> p.second;
    return is;
}

class Solver
{
private:
    std::string s;
    int cnt;

public:
    Solver()
    {
        std::cin >> s;
        cnt = 0;
    }
    ~Solver() {}
    void solve()
    {
        std::function<bool(std::string s)> check = [&](std::string s) -> bool
        {
            if (s.size() == 1)
            {
                return std::stoi(s) % 3 == 0;
            }
            cnt++;
            ll sum = std::accumulate(s.begin(), s.end(), 0, [](ll a, char b) -> ll
                                     { return a + (b - '0'); });
            return check(std::to_string(sum));
        };
        if (check(s))
        {
            std::cout << cnt << '\n'
                      << "YES";
        }
        else
        {
            std::cout << cnt << '\n'
                      << "NO";
        }
    }
};

int main()
{
    fastio;
    Solver solver;
    solver.solve();
    return 0;
}