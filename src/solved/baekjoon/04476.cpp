#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                    \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

std::ostream &operator<<(std::ostream &os, const std::vector<int> &v)
{
    for (const auto &x : v)
        os << std::setw(3) << std::setfill(' ') << x;
    return os;
}

class Solver
{
private:
    std::vector<int> laser;
    void rotate(std::vector<int> &v)
    {
        int n = static_cast<int>(v.size());
        std::vector<int> result(n);
        for (int i = 0; i < n; i++)
            result[v[i]] = n - i - 1;
        v = result;
    }
    void mirror(std::vector<int> &v)
    {
        int n = static_cast<int>(v.size());
        std::vector<int> result(n);
        for (int i = 0; i < n; i++)
            result[i] = n - v[i] - 1;
        v = result;
    }

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        int size;
        while (std::cin >> size)
        {
            if (size == 0)
                break;
            laser.clear();
            laser.resize(size);
            for (auto &i : laser)
                std::cin >> i;

            // 1. original
            std::cout << laser << '\n';

            // 2. 90 CW rotation
            rotate(laser);
            std::cout << laser << '\n';

            // 3. 180 CW rotation
            rotate(laser);
            std::cout << laser << '\n';

            // 4. 270 CW rotation
            rotate(laser);
            std::cout << laser << '\n';

            // 5. mirror
            rotate(laser);
            mirror(laser);
            std::cout << laser << '\n';

            // 6. 90 CW rotation
            rotate(laser);
            std::cout << laser << '\n';

            // 7. 180 CW rotation
            rotate(laser);
            std::cout << laser << '\n';

            // 8. 270 CW rotation
            rotate(laser);
            std::cout << laser << '\n';

            // additional newline
            std::cout << "\n";
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