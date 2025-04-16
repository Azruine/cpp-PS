/*==== Copyright 2025 Azruine ====*/

#include <vector>

class UnionFind {
private:
    std::vector<size_t> data;

public:
    void init(size_t n) {
        data.resize(n);
        for (size_t i = 0; i < n; i++) {
            data[i] = i;
        }
    }
    size_t find(size_t x) { return x == data[x] ? x : data[x] = find(data[x]); }
    void merge(size_t x, size_t y) {
        x = find(x), y = find(y);
        if (x != y) {
            x > y ? data[x] = y : data[y] = x;
        }
    }
};
