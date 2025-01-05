#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define fastio                             \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

std::ostream &operator<<(std::ostream &os, std::pair<int, int> p)
{
    os << p.second << ' ' << p.first;
    return os;
}

class SegmentTreeMinMax
{
private:
    int size;
    // max, min
    std::vector<std::pair<int, int>> tree;

public:
    SegmentTreeMinMax()
    {
        std::cin >> size;
        int trash;
        std::cin >> trash;
        tree.resize(2 * size);
    }
    ~SegmentTreeMinMax() {}

    void init()
    {
        int temp;
        for (int i = 0; i < size; i++)
        {
            std::cin >> temp;
            tree[i + size] = {temp, temp};
        }
        build();
    }
    void build()
    {
        for (int i = size - 1; i > 0; i--)
        {
            tree[i].first = std::max(tree[i << 1].first, tree[i << 1 | 1].first);
            tree[i].second = std::min(tree[i << 1].second, tree[i << 1 | 1].second);
        }
    }
    std::pair<int, int> query(int l, int r)
    {
        std::pair<int, int> res = {INT_MIN, INT_MAX};
        int l0 = l + size, r0 = r + size;
        for (; l0 < r0; l0 >>= 1, r0 >>= 1)
        {
            if (l0 & 1)
            {
                res.first = std::max(res.first, tree[l0].first);
                res.second = std::min(res.second, tree[l0].second);
                l0++;
            }
            if (r0 & 1)
            {
                r0--;
                res.first = std::max(res.first, tree[r0].first);
                res.second = std::min(res.second, tree[r0].second);
            }
        }
        return res;
    }
};

class Solver
{
private:
    int n;
    SegmentTreeMinMax st;

public:
    Solver()
    {
        st.init();
    }
    ~Solver() {}
    void solve()
    {
        int a, b;
        while (std::cin >> a >> b)
        {
            std::cout << st.query(a - 1, b) << "\n";
        }
    }
};

int main()
{
    fastio;
    Solver solver;
    solver.solve();
    return 0;
}