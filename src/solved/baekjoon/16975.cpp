#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                    \
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

    /**
     * @brief Apply lazy propagation to the node p
     * @param index The index of the node
     * @param value The value to be added to the node
     * @return void
     */
    void apply(int index, ll value)
    {
        tree[index] += value;
        if (index < size)
            lazy[index] += value;
    }
    
    /**
     * @brief Build the segment tree
     * @param index The index of the node
     * @return void
     */
    void build(int index)
    {
        while (index > 1)
        {
            index >>= 1;
            tree[index] = tree[index << 1] + tree[index << 1 | 1] + lazy[index];
        }
    }

    /**
     * @brief Push the lazy propagation down to the children
     * @param index The index of the node
     * @return void
     */
    void push(int index)
    {
        for (int s = height; s > 0; --s)
        {
            int i = index >> s;
            if (lazy[i] != 0)
            {
                apply(i << 1, lazy[i]);
                apply(i << 1 | 1, lazy[i]);
                lazy[i] = 0;
            }
        }
    }

public:
    SegmentTree() {}
    ~SegmentTree() {}

    /**
     * @brief Initialize the segment tree
     * @param n The size of the segment tree
     * @return void
     */
    void init(int n)
    {
        size = n;
        height = sizeof(int) * 8 - __builtin_clz(size);
        tree.resize(size << 1);
        lazy.assign(size, 0);
        for (int i = size; i < size << 1; i++)
            std::cin >> tree[i];
        build(1);
    }

    /**
     * @brief Increment the value of the range [l, r) by value
     * @param l The left index of the range
     * @param r The right index of the range
     * @param value The value to be added to the range
     * @return void
     */
    void inc(int l, int r, ll value)
    {
        l += size;
        r += size;
        int l0 = l;
        int r0 = r;
        for (; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                apply(l++, value);
            if (r & 1)
                apply(--r, value);
        }
        build(l0);
        build(r0 - 1);
    }

    /**
     * @brief Query the value of the index
     * @param index The index of the value
     * @return The value of the index
     */
    ll query(int index)
    {
        index += size;
        push(index);
        return tree[index];
    }

    /**
     * @brief Query the value of the range [l, r)
     * @param l The left index of the range
     * @param r The right index of the range
     * @return The value of the range
     */
    ll query(int l, int r)
    {
        l += size;
        r += size;
        push(l);
        push(r - 1);
        int res = 0;
        for (; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                res += tree[l++];
            if (r & 1)
                res += tree[--r];
        }
        return res;
    }
};

class Solver
{
private:
    SegmentTree st;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        int n;
        std::cin >> n;
        st.init(n);
        int m;
        std::cin >> m;
        while (m--)
        {
            int op;
            std::cin >> op;
            if (op == 1)
            {
                int l, r, v;
                std::cin >> l >> r >> v;
                st.inc(l - 1, r, v);
            }
            else
            {
                int i;
                std::cin >> i;
                std::cout << st.query(i - 1) << '\n';
            }
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