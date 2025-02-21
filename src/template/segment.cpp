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