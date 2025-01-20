#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                          \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

template <typename T>
struct Point
{
    T x, y;
    Point() : x(0), y(0) {}
    ld getAngle() const
    {
        return atan2(y, x);
    }
    void rotate(ld angle)
    {
        ld nx = x * cos(angle) - y * sin(angle);
        ld ny = x * sin(angle) + y * cos(angle);
        x = nx;
        y = ny;
    }
    void shift(const Point &p)
    {
        x -= p.x;
        y -= p.y;
    }
};

template <typename T>
std::istream &operator>>(std::istream &in, Point<T> &p)
{
    in >> p.x >> p.y;
    return in;
}

class Solver
{
private:
    Point<ld> a, b, c, d;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> a >> b >> c >> d;
        b.shift(a);
        c.shift(a);
        d.shift(a);
        // b to x axis
        ld angle = b.getAngle();
        b.rotate(-angle);
        c.rotate(-angle);
        d.rotate(-angle);
        // check y value of c and d
        if (c.y * d.y < 0)
        {
            // check x value of CD line
            ld x = c.x + (d.x - c.x) * abs(c.y) / abs(d.y - c.y);
            if (b.x * x > 1e-9 && abs(b.x) - abs(x) > 1e-9)
            {
                std::cout << 1;
                return;
            }
        }
        std::cout << 0;
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}