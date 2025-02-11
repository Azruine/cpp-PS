#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                         \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

std::array<std::pair<int, int>, 4> dir = {{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};

class Solver
{
private:
    int n, m;
    std::vector<std::vector<int>> pic;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> n >> m;
        pic.assign(n, std::vector<int>(m));
        for (auto &v : pic)
            for (auto &c : v)
                std::cin >> c;

        int ret = 0;
        int cnt = 0;
        std::queue<std::pair<int, int>> q;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (pic[i][j] == 1)
                {
                    cnt++;
                    q.push({i, j});
                    pic[i][j] = -1;
                    int area = 1;
                    while (!q.empty())
                    {
                        auto [curX, curY] = q.front();
                        q.pop();
                        for (auto [dx, dy] : dir)
                        {
                            auto nextX = curX + dx, nextY = curY + dy;
                            if (nextX >= 0 && nextX < n && nextY >= 0 && nextY < m && pic[nextX][nextY] == 1)
                            {
                                pic[nextX][nextY] = -1;
                                q.push({nextX, nextY});
                                area++;
                            }
                        }
                    }
                    ret = std::max(ret, area);
                }
            }
        }
        std::print("{}\n{}", cnt, ret);
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}