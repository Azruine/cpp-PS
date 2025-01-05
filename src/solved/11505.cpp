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
    int MOD = 1'000'000'007;
    int size;
    int height;
    std::vector<ll> tree;
    std::vector<ll> lazy;

public:
    SegmentTree()
    {
        std::cin >> size;
        int trash;
        std::cin >> trash;
        std::cin >> trash;
        height = (sizeof(ll) * 8 - __builtin_clz(size));
        tree.resize(2 * size);
        lazy.assign(2 * size, 1ll);
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
            tree[i] = (tree[i << 1] * tree[i << 1 | 1]) % MOD;
    }
    void apply(int p, ll value)
    {
        tree[p] = (tree[p] * value) % MOD;
        if (p < size)
            lazy[p] = (lazy[p] * value) % MOD;
    }
    void pushDown(int p)
    {
        ll value = lazy[p];
        if (value != 1)
        {
            apply(p << 1, value);
            apply(p << 1 | 1, value);
            lazy[p] = 1;
        }
    }
    void push(int p)
    {
        for (int s = height; s > 0; s--)
        {
            int i = p >> s;
            if (i > 0)
                pushDown(i);
        }
    }
    void update(int l, int r, ll value)
    {
        if (l >= r)
            return;
        push(l + size);
        push(r + size - 1);

        int l0 = l + size, r0 = r + size;
        for (; l0 < r0; l0 >>= 1, r0 >>= 1)
        {
            if (l0 & 1)
                apply(l0++, value);
            if (r0 & 1)
                apply(--r0, value);
        }
        buildUp(l + size);
        buildUp(r + size - 1);
    }
    void buildUp(int p)
    {
        while (p > 1)
        {
            p >>= 1;
            tree[p] = (tree[p << 1] * tree[p << 1 | 1]) % MOD;
            tree[p] = (tree[p] * lazy[p]) % MOD;
        }
    }
    ll query(int l, int r)
    {
        if (l >= r)
            return 1;
        push(l + size);
        push(r + size - 1);

        ll res = 1;
        for (l += size, r += size; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                res = (res * tree[l++]) % MOD;
            if (r & 1)
                res = (res * tree[--r]) % MOD;
        }
        return res;
    }

    void modify(int p, ll value)
    {
        p += size;
        push(p);
        tree[p] = value;
        buildUp(p);
    }
};

class Solver
{
private:
    int n;
    SegmentTree st;

public:
    Solver()
    {
        st.init();
    }
    ~Solver() {}
    void solve()
    {
        ll q, a, b;
        while (std::cin >> q >> a >> b)
        {
            if (q == 1)
                st.modify(a - 1, b);
            else if (q == 2)
                std::cout << st.query(a - 1, b) << '\n';
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