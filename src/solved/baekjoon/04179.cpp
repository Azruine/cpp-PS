#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;
using point = std::pair<int, int>;

#define 고속입출력                         \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

std::array<std::pair<int, int>, 4> dir = {{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};

class Solver
{
private:
    int n, m;
    std::vector<std::vector<char>> maze;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> n >> m;
        maze.assign(n, std::vector<char>(m));
        std::vector<std::vector<int>> FIREEEEEEE(n, std::vector<int>(m, INT_MAX));
        point start;
        std::queue<std::pair<int, point>> FIRE;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                std::cin >> maze[i][j];
                if (maze[i][j] == 'J')
                    start.first = i, start.second = j;
                else if (maze[i][j] == 'F')
                {
                    FIRE.push({0, {i, j}});
                    FIREEEEEEE[i][j] = 0;
                }
            }
        }

        while (!FIRE.empty())
        {
            auto [curDist, curPoint] = FIRE.front();
            FIRE.pop();
            for (auto &[dx, dy] : dir)
            {
                auto nextX = curPoint.first + dx, nextY = curPoint.second + dy, nextDist = curDist + 1;
                if (nextX >= 0 && nextX < n &&
                    nextY >= 0 && nextY < m &&
                    maze[nextX][nextY] == '.' &&
                    FIREEEEEEE[nextX][nextY] == INT_MAX)
                {
                    FIREEEEEEE[nextX][nextY] = nextDist;
                    FIRE.push({nextDist, {nextX, nextY}});
                }
            }
        }

        std::queue<std::pair<int, point>> q;
        q.push({0, start});
        std::vector<std::vector<int>> distance(n, std::vector<int>(m, -1));
        distance[start.first][start.second] = 0;
        int ans = INT_MAX;
        while (!q.empty())
        {
            auto [curDist, curPoint] = q.front();
            q.pop();
            for (auto &[dx, dy] : dir)
            {
                auto nextX = curPoint.first + dx, nextY = curPoint.second + dy, nextDist = curDist + 1;
                if (nextX >= 0 && nextX < n &&
                    nextY >= 0 && nextY < m &&
                    maze[nextX][nextY] == '.' &&
                    distance[nextX][nextY] == -1 &&
                    nextDist < FIREEEEEEE[nextX][nextY])
                {
                    distance[nextX][nextY] = curDist + 1;
                    q.push({curDist + 1, {nextX, nextY}});
                }
                if (nextX < 0 || nextX >= n ||
                    nextY < 0 || nextY >= m)
                {
                    ans = std::min(ans, nextDist);
                }
            }
        }
        if (ans == INT_MAX)
            std::println("IMPOSSIBLE");
        else
            std::println("{}", ans);
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}