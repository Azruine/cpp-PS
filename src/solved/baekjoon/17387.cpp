#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                    \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

template <typename T>
struct Point
{
    T x, y;
    Point() : x(0), y(0) {}
    Point(T x, T y) : x(x), y(y) {}

    Point operator-(const Point &p) const
    {
        return Point(x - p.x, y - p.y);
    }
};

int ccw(const Point<int> &a, const Point<int> &b, const Point<int> &c)
{
    ll ret = ((ll)a.x * b.y + (ll)b.x * c.y + (ll)c.x * a.y) - ((ll)a.y * b.x + (ll)b.y * c.x + (ll)c.y * a.x);
    if (ret > 0)
        return 1;
    else if (ret < 0)
        return -1;
    else
        return 0;
}

template <typename T>
std::istream &operator>>(std::istream &in, Point<T> &p)
{
    in >> p.x >> p.y;
    return in;
}

class Solver
{
private:
    Point<int> a, b, c, d;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> a >> b >> c >> d;
        // get slope vector of ab and cd
        Point<int> ab = b - a;
        Point<int> cd = d - c;
        // if the slope vector of ab and cd are same, then they are parallel
        if ((ll)ab.x * cd.y == (ll)ab.y * cd.x)
        {
            // check if the two lines are same
            int ccwValue = ccw(a, b, c);
            if (ccwValue == 0)
            {
                // reflect the points to x axis
                std::vector<int> reflection = {a.x, b.x, c.x, d.x};
                // if the line is parallel to y axis, reflect the points to y axis
                if (a.x == b.x)
                    reflection = {a.y, b.y, c.y, d.y};

                // sort the reflection points
                if (reflection[0] > reflection[1])
                {
                    std::swap(reflection[0], reflection[1]);
                    std::swap(a, b);
                }
                if (reflection[2] > reflection[3])
                {
                    std::swap(reflection[2], reflection[3]);
                    std::swap(c, d);
                }

                // Case 1. c or d included in (a, b) || a or b included in (c, d) -> print 1
                if ((reflection[2] > reflection[0] && reflection[2] < reflection[1]) || (reflection[3] > reflection[0] && reflection[3] < reflection[1]) || (reflection[0] > reflection[2] && reflection[0] < reflection[3]) || (reflection[1] > reflection[2] && reflection[1] < reflection[3]))
                    std::cout << "1\n";

                // Case 1-1. {a, b} == {c, d} -> print 1
                else if (reflection[0] == reflection[2] && reflection[1] == reflection[3])
                    std::cout << "1\n";

                // Case 2. c or d equal to a or b -> print 1 and intersection point
                else if (reflection[2] == reflection[0] || reflection[2] == reflection[1] || reflection[3] == reflection[0] || reflection[3] == reflection[1])
                {
                    std::cout << "1\n";
                    // if (reflection[2] == reflection[0] || reflection[2] == reflection[1])
                    //     std::cout << c.x << ' ' << c.y;
                    // else
                    //     std::cout << d.x << ' ' << d.y;
                }

                // Case 3. no intersection -> print 0
                else
                    std::cout << "0\n";
            }
            // lines are parallel but not same
            else
                std::cout << "0\n";
        }

        // if the slope vector of ab and cd are not same, get intersection point
        else
        {
            ll det = (ll)ab.x * cd.y - (ll)ab.y * cd.x;
            ll dx = c.x - a.x;
            ll dy = c.y - a.y;
            ld t = (ld)(dx * cd.y - dy * cd.x) / det;
            ld u = (ld)(dx * ab.y - dy * ab.x) / det;

            // intersection point is in the range of ab and cd
            if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
            {
                std::cout << "1\n";
                // std::cout << std::fixed << std::setprecision(10) << (ld)a.x + (ld)ab.x * t << ' ' << (ld)a.y + (ld)ab.y * t;
            }

            // intersection point is not in the range of ab and cd
            else
                std::cout << "0\n";
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