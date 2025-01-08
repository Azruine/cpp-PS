#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define fastio                             \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class Seg
{
private:
    int size;
    std::vector<int> tree;

public:
    Seg() {}
    ~Seg() {}
    Seg(int n)
    {
        size = n;
        tree.assign(size << 1, INT_MAX);
    }
    Seg(std::stringstream &ss)
    {
        ss >> size;
        tree.assign(size << 1, 0);
        init(ss);
    }
    void init()
    {
        for (int i = size; i < size << 1; i++)
            std::cin >> tree[i];
        build();
    }
    void init(std::stringstream &ss)
    {
        tree.assign(size << 1, 0);
        for (int i = size; i < size << 1; i++)
            ss >> tree[i];
        build();
    }
    void build()
    {
        for (int i = size - 1; i > 0; i--)
            tree[i] = std::min(tree[i << 1], tree[i << 1 | 1]);
    }
    int query(int i)
    {
        return tree[i + size];
    }
    int query(int l, int r)
    {
        if (l == r - 1)
            return tree[l + size];
        int res = INT_MAX;
        int l0 = l + size, r0 = r + size;
        for (; l0 < r0; l0 >>= 1, r0 >>= 1)
        {
            if (l0 & 1)
                res = std::min(res, tree[l0++]);
            if (r0 & 1)
                res = std::min(res, tree[--r0]);
        }
        return res;
    }
    int getRightIdx(int l, int r, int value)
    {
        int l0 = l;
        while (l < r)
        {
            int mid = (l + r) >> 1;
            int midQuery = query(l0, mid + 1);
            if (midQuery < value)
                r = mid;
            else
                l = mid + 1;
        }
        return l;
    }
    int getLeftIdx(int l, int r, int value)
    {
        int r0 = r;
        while (l < r)
        {
            int mid = (l + r) >> 1;
            int midQuery = query(mid, r0);
            if (midQuery < value)
                l = mid + 1;
            else
                r = mid;
        }
        return l;
    }
    ll getMaxArea()
    {
        ll maxArea = INT64_MIN;
        for (int i = 0; i < size; i++)
        {
            int cur = query(i);
            int leftIdx = getLeftIdx(0, i, cur);
            int rightIdx = getRightIdx(i + 1, size, cur);
            maxArea = std::max(maxArea, static_cast<ll>(cur) * (rightIdx - leftIdx));
        }
        return maxArea;
    }
};

class Solver
{
private:
    int n;

    Seg seg;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> n;
        seg = Seg(n);
        seg.init();
        std::cout << seg.getMaxArea() << "\n";
    }
};

int main()
{
    fastio;
    Solver solver;
    solver.solve();
    return 0;
}