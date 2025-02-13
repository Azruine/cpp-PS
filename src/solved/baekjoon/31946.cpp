#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                         \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

using point = std::pair<int, int>;

class Solver
{
private:
    int n, m, s;
    std::vector<std::vector<int>> map;
    bool isValid(int r, int c)
    {
        return (r >= 0 && r < n) &&
               (c >= 0 && c < m);
    }

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> n >> m;
        map.assign(n, std::vector<int>(m));
        for (auto &v : map)
            for (auto &i : v)
                std::cin >> i;
        std::cin >> s;
        int startColor = map[0][0];
        std::vector<std::vector<int>> dist(n, std::vector<int>(m, -1));
        std::queue<std::pair<int, point>> q;
        q.push({0, {0, 0}});
        while (!q.empty())
        {
            auto [curDist, curPoint] = q.front();
            q.pop();
            for (int rNext = curPoint.first - s; rNext <= curPoint.first + s; rNext++)
            {
                int gap = std::abs(rNext - curPoint.first);
                for (int cNext = curPoint.second - s + gap; cNext <= curPoint.second + s - gap; cNext++)
                {
                    if (isValid(rNext, cNext) && map[rNext][cNext] == startColor && dist[rNext][cNext] == -1)
                    {
                        q.push({curDist + 1, {rNext, cNext}});
                        dist[rNext][cNext] = curDist + 1;
                    }
                }
            }
        }
        std::cout << (dist[n - 1][m - 1] == -1 ? "DEAD" : "ALIVE");
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}