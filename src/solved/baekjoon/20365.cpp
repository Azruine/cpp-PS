#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                          \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class Solver
{
private:
    std::string s;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        int n = 1, l;
        std::cin >> l >> s;
        for (int i = 0; i < l - 1; i++)
        {
            if (s[i] != s[i + 1])
                n++;
        }
        std::cout << (n >> 1) + 1;
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}