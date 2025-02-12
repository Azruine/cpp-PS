#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                         \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

using point = std::pair<int, int>;
std::array<point, 4> direction = {{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};
enum STATE
{
    H,
    V
};
point operator+(point &p1, point &p2)
{
    return {p1.first + p2.first, p1.second + p2.second};
}

class Solver
{
private:
    int n;
    std::vector<std::vector<char>> map;
    bool isValidH(point p)
    {
        int r = p.first, c = p.second;
        return (r < n && r >= 0) && (c < n - 1 && c >= 1) && map[r][c + 1] != '1' && map[r][c - 1] != '1' && map[r][c] != '1';
    }
    bool isValidV(point p)
    {
        int r = p.first, c = p.second;
        return (r < n - 1 && r >= 1) && (c < n && c >= 0) && map[r + 1][c] != '1' && map[r - 1][c] != '1' && map[r][c] != '1';
    }
    bool canRotate(point p)
    {
        int r = p.first, c = p.second;
        return (r < n - 1 && r >= 1) && (c < n - 1 && c >= 1) &&
               map[r][c + 1] != '1' && map[r][c - 1] != '1' &&
               map[r + 1][c] != '1' && map[r - 1][c] != '1' &&
               map[r + 1][c + 1] != '1' && map[r - 1][c - 1] != '1' &&
               map[r + 1][c - 1] != '1' && map[r - 1][c + 1] != '1' &&
               map[r][c] != '1';
    }
    bool (Solver::*valid[2])(point) = {&Solver::isValidH, &Solver::isValidV};

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> n;
        map.assign(n, std::vector<char>(n));
        std::vector<point> startVec, endVec;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                std::cin >> map[i][j];
                if (map[i][j] == 'B')
                    startVec.push_back({i, j});
                else if (map[i][j] == 'E')
                    endVec.push_back({i, j});
            }
        }
        point start = startVec[1], end = endVec[1];
        STATE startState, endState;
        if (startVec[0].first == startVec[1].first)
            startState = H;
        else
            startState = V;
        if (endVec[0].first == endVec[1].first)
            endState = H;
        else
            endState = V;
        std::queue<std::tuple<point, STATE, int>> q;
        std::vector<std::vector<std::array<int, 2>>> dist(n, std::vector<std::array<int, 2>>(n, {{-1, -1}}));
        q.push({start, startState, 0});
        dist[start.first][start.second][startState] = 0;
        while (!q.empty())
        {
            auto [curPoint, curState, curDist] = q.front();
            q.pop();
            // moving
            for (auto dir : direction)
            {
                auto nextPoint = curPoint + dir;
                auto nextState = curState;
                auto nextDist = curDist + 1;
                if ((this->*valid[nextState])(nextPoint) &&
                    dist[nextPoint.first][nextPoint.second][nextState] == -1)
                {
                    q.push({nextPoint, nextState, nextDist});
                    dist[nextPoint.first][nextPoint.second][nextState] = nextDist;
                }
            }
            // rotating
            {
                auto nextPoint = curPoint;
                auto nextState = curState == H ? V : H;
                auto nextDist = curDist + 1;
                if (canRotate(nextPoint) &&
                    dist[nextPoint.first][nextPoint.second][nextState] == -1)
                {
                    q.push({nextPoint, nextState, nextDist});
                    dist[nextPoint.first][nextPoint.second][nextState] = nextDist;
                }
            }
        }
        std::cout << std::max(dist[end.first][end.second][endState], 0);
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}