#include <bits/stdc++.h>
class SegTree {
private:
    int height;
    int size;
    std::vector<int> data;
    std::vector<int> delay;

public:
    SegTree() {}
    ~SegTree() {}
    void init(int n) {
        size = n;
        height = sizeof(int) * 8 - __builtin_clz(size);
        data.assign(size << 1, 0);
        delay.assign(size, 0);
    }
    void apply(int pos, int value) {
        data[pos] += value;
        if (pos < size) {
            delay[pos] = value;
        }
    }
    void build(int pos) {
        while (pos > 1) {
            pos >>= 1;
            data[pos] = data[pos << 1] + data[pos << 1 | 1] + delay[pos];
        }
    }
    void push(int pos) {
        for (int s = height; s > 0; --s) {
            int i = pos >> s;
            if (delay[i] != 0) {
                apply(i << 1, delay[i]);
                apply(i << 1 | 1, delay[i]);
                delay[i] = 0;
            }
        }
    }
    void increase(int l, int r, int value) {
        l += size, r += size;
        int l0 = l, r0 = r;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) apply(l++, value);
            if (r & 1) apply(--r, value);
        }
        build(l0);
        build(r0 - 1);
    }
    int query(int l, int r) {
        l += size, r += size;
        push(l);
        push(r - 1);
        int res = 0;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += data[l++];
            if (r & 1) res += data[--r];
        }
        return res;
    }
};

class SegTreeMax {
private:
    int height;
    int size;
    std::vector<int> tree;
    std::vector<int> delay;

public:
    SegTreeMax() {}
    ~SegTreeMax() {}
    void init(int n) {
        height = sizeof(int) * 8 - __builtin_clz(n);
        size = n;
        tree.resize(2 * n, 0);
        delay.resize(n, 0);
    }
    void buildAll() {
        for (int i = size - 1; i > 0; i--) {
            tree[i] = std::max(tree[i << 1], tree[i << 1 | 1]);
        }
    }
    void setLeaf(std::vector<int>& nums) {
        for (int i = 0; i < size; i++) {
            tree[size + i] = nums[i];
        }
    }
    void apply(int pos, int value) {
        tree[pos] += value;
        if (pos < size) delay[pos] += value;
    }
    void build(int pos) {
        while (pos > 1) {
            pos >>= 1;
            tree[pos] =
                std::max(tree[pos << 1], tree[pos << 1 | 1]) + delay[pos];
        }
    }
    void push(int pos) {
        for (int s = height; s > 0; s--) {
            int i = pos >> s;
            if (delay[i] != 0) {
                apply(i << 1, delay[i]);
                apply(i << 1 | 1, delay[i]);
                delay[i] = 0;
            }
        }
    }
    void increase(int l, int r, int value) {
        l += size, r += size;
        int l0 = l, r0 = r;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) apply(l++, value);
            if (r & 1) apply(--r, value);
        }
        build(l0);
        build(r0 - 1);
    }
    int query(int l, int r) {
        l += size, r += size;
        push(l);
        push(r - 1);
        int res = INT_MIN;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = std::max(res, tree[l++]);
            if (r & 1) res = std::max(res, tree[--r]);
        }
        return res;
    }
};