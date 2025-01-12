#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                    \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class Solver
{
private:
    std::array<int, 10> function = {};
    std::array<int, 10> reverse = {};

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        for (auto &i : function)
            std::cin >> i;
        for (int i = 0; i < 10; i++)
            reverse[function[i]] = i;
        int a, b, f_a, f_b;
        std::cin >> f_a >> f_b;
        a = getReverse(f_a);
        b = getReverse(f_b);
        std::cout << getFunction(a + b) << '\n';
    }
    int getFunction(int a)
    {
        std::string s = std::to_string(a);
        return std::accumulate(s.begin(), s.end(), 0, [&](int res, char c) { return res * 10 + function[c - '0']; });
    }
    int getReverse(int a)
    {
        std::string s = std::to_string(a);
        return std::accumulate(s.begin(), s.end(), 0, [&](int res, char c) { return res * 10 + reverse.at(c - '0'); });
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}