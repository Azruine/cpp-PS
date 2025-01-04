#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define fastio                             \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

template <typename T>
void transpose(std::vector<std::vector<T>> &v)
{
    int n = v.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            std::swap(v[i][j], v[j][i]);
}

class Solver
{
private:
    int n;
    std::vector<std::vector<char>> v;

public:
    Solver()
    {
        std::cin >> n;
        v.assign(n, std::vector<char>(n));
        for (auto &i : v)
            for (auto &j : i)
                std::cin >> j;
    }
    ~Solver() {}
    void solve()
    {
        auto count = [&](char delim) -> int
        {
            int cnt = 0;
            for (auto &string : v)
            {
                std::stringstream ss(std::string(string.begin(), string.end()));
                for (std::string seg; std::getline(ss, seg, delim);)
                    if (seg.size() >= 2)
                        cnt++;
            }
            return cnt;
        };
        std::cout << count('X') << " ";
        transpose(v);
        std::cout << count('X') << "\n";
    }
};

int main()
{
    fastio;
    Solver solver;
    solver.solve();
    return 0;
}