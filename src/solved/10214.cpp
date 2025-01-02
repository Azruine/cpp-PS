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
    int t;
    int n;
    std::vector<std::pair<int, int>> arr;

public:
    Solver()
    {
        std::cin >> t;
        n = 9;
    }
    ~Solver() {}
    void solve()
    {
        while (t--)
        {
            int a = 0, b = 0;
            std::pair<int, int> p;
            for (int i = 0; i < n; i++)
            {
                std::cin >> p;
                a += p.first, b += p.second;
            }
            std::cout << (a > b ? "Yonsei" : (a < b ? "Korea" : "Draw")) << "\n";
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