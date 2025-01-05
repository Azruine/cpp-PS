#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define fastio                             \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class SegmentTree
{
private:
    int size;
    int height;
    std::vector<ll> tree;
    std::vector<ll> lazy;

public:
    SegmentTree() {}
    SegmentTree(int n)
    {
        size = n;
        height = (sizeof(ll) * 8 - __builtin_clz(n));
        tree.resize(2 * size);
        lazy.resize(size);
        lazy.assign(size, 0);
    }
    ~SegmentTree() {}
    void init()
    {
        for (int i = 0; i < size; i++)
            std::cin >> tree[i + size];
        build();
    }
    void build()
    {
        for (int i = size - 1; i > 0; i--)
            tree[i] = tree[i << 1] + tree[i << 1 | 1];
    }
    void modify(int p, int value)
    {
        for (tree[p += size] = value; p > 1; p >>= 1)
            tree[p >> 1] = tree[p] + tree[p ^ 1];
    }
    void modify(int l, int r, int value)
    {
        for (l += size, r += size; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                tree[l++] += value;
            if (r & 1)
                tree[--r] += value;
        }
    }
    ll query(int p)
    {
        ll res = 0;
        for (p += size; p > 0; p >>= 1)
            res += tree[p];
        return res;
    }
    ll query(int l, int r)
    {
        ll res = 0;
        for (l += size, r += size; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                res += tree[l++];
            if (r & 1)
                res += tree[--r];
        }
        return res;
    }
    void push()
    {
        for (int i = 1; i < size; i++)
        {
            tree[i << 1] += tree[i];
            tree[i << 1 | 1] += tree[i];
            tree[i] = 0;
        }
    }
};

class Solver
{
private:
    int n;
    int t;
    SegmentTree st;

public:
    Solver()
    {
        std::cin >> n >> t;
        st = SegmentTree(n);
        st.init();
    }
    ~Solver() {}
    void solve()
    {
        int l, r, p, value;
        while (t--)
        {
            std::cin >> l >> r >> p >> value;
            if (l > r)
                std::swap(l, r);
            std::cout << st.query(l - 1, r) << "\n";
            st.modify(p - 1, value);
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