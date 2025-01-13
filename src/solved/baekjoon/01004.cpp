#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                    \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

using point = std::pair<int, int>;

std::istream &operator>>(std::istream &is, point &p)
{
    is >> p.first >> p.second;
    return is;
}

/**
 * @brief get the squared euclidean distance between two points
 * @param a the first point
 * @param b the second point
 * @return the squared euclidean distance between two points
 */
int getEuclideanDistance(point a, point b)
{
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

/**
 * @brief check if the point is inside the circle
 * @param p the point
 * @param c the center of the circle
 * @param r the radius of the circle
 * @return true if the point is inside the circle, false otherwise
 */
bool isInsideCircle(point p, point c, int r)
{
    return getEuclideanDistance(p, c) < r * r;
}

class Solver
{
private:
    int t;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> t;
        while (t--)
        {
            point start, end;
            std::cin >> start >> end;
            int n;
            std::cin >> n;
            std::vector<std::pair<point, int>> circles(n);
            for (auto &i : circles)
                std::cin >> i.first >> i.second;
            std::println("{}", std::accumulate(circles.begin(), circles.end(), 0, [&](int acc, std::pair<point, int> circle) {
                return acc + (isInsideCircle(start, circle.first, circle.second) ^ isInsideCircle(end, circle.first, circle.second));
            }));
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