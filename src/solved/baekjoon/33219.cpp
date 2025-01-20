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
    ld x, y;
    Point() : x(0), y(0) {}
    Point(ld x, ld y) : x(x), y(y) {}

    ld getDistance(const Point &p) const
    {
        return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
    }
};

struct Circle
{
    Point center;
    ld radius;
    Circle() : center(Point()), radius(0) {}
    Circle(Point center, ld radius) : center(center), radius(radius) {}
    bool isInside(const Point &p) const
    {
        return center.getDistance(p) < radius;
    }
};

class Solver
{
private:
    ld minX = -20;
    ld maxX = 20;
    ld minY = -10;
    ld maxY = 10;
    ld interval = 1e-5;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::vector<Circle> circles;
        int n;
        std::cin >> n;
        for (int i = 0; i < n; i++)
        {
            ld x, r;
            std::cin >> x >> r;
            circles.emplace_back(Circle(Point(x, 0), r));
        }
        std::sort(circles.begin(), circles.end(), [](const Circle &a, const Circle &b) {
            return a.center.x - a.radius < b.center.x - b.radius;
        });
        ld left = minX;
        ld area = 0;
        while (left <= maxX)
        {
            ld height = -1e10;
            for (auto const &circle : circles)
            {
                if (circle.center.x + circle.radius < left)
                    continue;
                if (circle.center.x - circle.radius > left)
                    break;
                ld dx = left - circle.center.x;
                ld dy = sqrt(circle.radius * circle.radius - dx * dx);
                height = std::max(height, circle.center.y + dy);
            }
            if (height > 1e-9)
                area += height * interval * 2;
            left += interval;
        }
        std::cout << std::fixed << std::setprecision(5) << area << "\n";
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}