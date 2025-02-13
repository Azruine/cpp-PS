#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                         \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class Solver
{
private:
    int i;
    std::unordered_map<int, int> map;
    int get(int n)
    {
        if (map.contains(n))
            return map[n];
        else
            return map[n] = (get(std::floor(n - sqrt(n))) + get(std::floor(log(n))) + get(std::floor(n * sin(n) * sin(n)))) % 1'000'000;
    }

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        map[0] = 1;
        while (std::cin >> i)
        {
            if (i < 0)
                return;
            std::cout << get(i) << '\n';
        }
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}