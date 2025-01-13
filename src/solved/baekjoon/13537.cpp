#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                          \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class SegmentTree
{
private:
    int size;
    std::vector<std::vector<int>> tree;
    void build()
    {
        for (int i = size - 1;i > 0; i--)
        {
            tree[i].resize(tree[i << 1].size() + tree[i << 1 | 1].size());
            std::merge(tree[i << 1].begin(), tree[i << 1].end(), tree[i << 1 | 1].begin(), tree[i << 1 | 1].end(), tree[i].begin());
        }
    }

public:
    SegmentTree() {}
    ~SegmentTree() {}
    void init(int n)
    {
        size = n;
        tree.assign(size << 1, std::vector<int>());
        for (int i = size; i < (size << 1); i++)
        {
            int x;
            std::cin >> x;
            tree[i].push_back(x);
        }
        build();
    }
    /**
     * @brief query the count of elements in the range [l, r) that are greater than k
     * @param l left bound of the range
     * @param r right bound of the range
     * @param k threshold value
     * @return the count of elements in the range [l, r) that are greater than k
     */
    int query(int l, int r, int k)
    {
        int res = 0;
        for (l += size, r += size; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
            {
                res += tree[l].end() - std::upper_bound(tree[l].begin(), tree[l].end(), k);
                l++;
            }
            if (r & 1)
            {
                --r;
                res += tree[r].end() - std::upper_bound(tree[r].begin(), tree[r].end(), k);
            }
        }
        return res;
    }
};

class Solver
{
private:
    SegmentTree st;
    int l, r, k;

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
            std::cin >> l >> r >> k;
            std::println("{}", st.query(l - 1, r, k));
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