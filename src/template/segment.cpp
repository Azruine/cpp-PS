#include <vector>
#include <iostream>

class SegmentTree
{
private:
    std::vector<int> tree;
    int size;

public:
    SegmentTree() {}
    ~SegmentTree() {}
    void init(int n)
    {
        size = n;
        tree.resize(n << 1);
        for (int i = size; i < size << 1; i++)
            std::cin >> tree[i];
        for (int i = size - 1; i; i--)
            tree[i] = tree[i << 1] + tree[i << 1 | 1];
    }
    int query(int l, int r)
    {
        int ret = 0;
        for (l += size, r += size; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                ret += tree[l++];
            if (r & 1)
                ret += tree[--r];
        }
        return ret;
    }
};