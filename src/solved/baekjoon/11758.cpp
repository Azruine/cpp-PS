#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                          \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

struct Point
{
    int x, y;
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
};

std::istream &operator>>(std::istream &in, Point &p)
{
    in >> p.x >> p.y;
    return in;
}

int ccw(Point a, Point b, Point c)
{
    ll ccw = (ll)a.x * b.y + (ll)b.x * c.y + (ll)c.x * a.y;
    ccw -= (a.y * b.x + b.y * c.x + c.y * a.x);
    if (ccw > 0)
        return 1;
    else if (ccw == 0)
        return 0;
    else
        return -1;
}

class Solver
{
private:
    int n;
    std::vector<Point> points;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        n = 3;
        points.resize(n);
        for (auto &p : points)
            std::cin >> p;
        std::print("{}", ccw(points[0], points[1], points[2]));
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}