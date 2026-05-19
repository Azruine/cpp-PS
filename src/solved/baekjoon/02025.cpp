#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                    \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class GraphSolver
{
private:
    int n;
    int startX, startY;
    std::array<std::pair<int, int>, 8> moves = {
        std::make_pair(2, 1),
        std::make_pair(1, 2),
        std::make_pair(-1, 2),
        std::make_pair(-2, 1),
        std::make_pair(-2, -1),
        std::make_pair(-1, -2),
        std::make_pair(1, -2),
        std::make_pair(2, -1)};
    std::vector<std::vector<bool>> visited;

    double getEuclideanDistance(int x1, int y1, int x2, int y2)
    {
        return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
    }
    std::vector<std::pair<int, int>> getNextMoves(int x, int y)
    {
        std::vector<std::pair<int, int>> nextMoves;
        for (auto move : moves)
        {
            int nextX = x + move.first;
            int nextY = y + move.second;
            if (nextX >= 0 && nextX < n && nextY >= 0 && nextY < n && !visited[nextX][nextY])
            {
                nextMoves.push_back(std::make_pair(nextX, nextY));
            }
        }
        std::sort(nextMoves.begin(), nextMoves.end(), [&](std::pair<int, int> &a, std::pair<int, int> &b) {
            if (getPossibleDegree(a.first, a.second) == getPossibleDegree(b.first, b.second))
            {
                return getEuclideanDistance(a.first, a.second, n >> 1, n >> 1) > getEuclideanDistance(b.first, b.second, n >> 1, n >> 1);
            }
            return getPossibleDegree(a.first, a.second) < getPossibleDegree(b.first, b.second);
        });
        return nextMoves;
    }
    int getPossibleDegree(int x, int y)
    {
        int degree = 0;
        for (auto move : moves)
        {
            int nextX = x + move.first;
            int nextY = y + move.second;
            if (nextX >= 0 && nextX < n && nextY >= 0 && nextY < n && !visited[nextX][nextY])
            {
                degree++;
            }
        }
        return degree;
    }

public:
    GraphSolver() {}
    ~GraphSolver() {}
    void solve()
    {
        std::cin >> n;
        std::cin >> startX >> startY;
        if (n & 1 && (startX + startY) & 1)
        {
            std::cout << "-1 -1";
            return;
        }
        startX--;
        startY--;

        visited.resize(n, std::vector<bool>(n, false));

        // warnsdorff's rule

        std::vector<std::pair<int, int>> path;
        path.push_back(std::make_pair(startX, startY));
        visited[startX][startY] = true;

        while (true)
        {
            auto current = path.back();
            auto nextMoves = getNextMoves(current.first, current.second);
            if (nextMoves.empty())
            {
                break;
            }
            auto next = nextMoves[0];
            visited[next.first][next.second] = true;
            path.push_back(next);
        }

        if (path.size() != n * n)
        {
            std::cout << "-1 -1";
        }
        else
        {
            std::for_each(path.begin(), path.end(), [](std::pair<int, int> &p) {
                std::cout << p.first + 1 << " " << p.second + 1 << "\n";
            });
        }
    }
};

int main()
{
    고속입출력;
    GraphSolver solver;
    solver.solve();
    return 0;
}
