#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                         \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

struct Point
{
    ld x, y;
    Point() : x(0), y(0) {}
    Point(ld x, ld y) : x(x), y(y) {}
};

ld getDistance(const Point &a, const Point &b)
{
    return sqrtl(powl((a.x - b.x), 2) + powl(a.y - b.y, 2));
}

std::istream &operator>>(std::istream &is, Point &p)
{
    is >> p.x >> p.y;
    return is;
}

struct Circle
{
    Point center;
    ld r;
};

std::istream &operator>>(std::istream &is, Circle &c)
{
    is >> c.center >> c.r;
    return is;
}

class Solver
{
private:
    Circle c1, c2;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> c1 >> c2;
        ld pi = std::numbers::pi_v<long double>;
        if (getDistance(c1.center, c2.center) >= (c1.r + c2.r))
        {
            std::cout << "0.000";
            return;
        }
        if (getDistance(c1.center, c2.center) <= std::fabsl(c1.r - c2.r))
        {
            std::cout << std::fixed << std::setprecision(3) << pi * powl(std::min(c1.r, c2.r), 2.0);
            return;
        }
        ld angle1, angle2;
        ld a = c1.r, b = c2.r, c = getDistance(c1.center, c2.center);
        angle1 = acosl((powl(a, 2) + powl(c, 2) - powl(b, 2)) / (a * c * 2.0));
        angle2 = acosl((powl(b, 2) + powl(c, 2) - powl(a, 2)) / (b * c * 2.0));
        ld area1 = c1.r * c1.r * angle1;
        ld area2 = c2.r * c2.r * angle2;
        ld area3 = a * b * sinl(pi - (angle1 + angle2));
        std::cout << std::fixed << std::setprecision(3) << area1 + area2 - area3;
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}