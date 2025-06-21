/*==== Copyright 2025 Azruine ====*/

#include <cstdint>
#include <vector>
class UnionFind {
public:
    void init(size_t n) {
        data.resize(n);
        rank.assign(n, 0);
        for (size_t i = 0; i < n; i++) {
            data[i] = i;
        }
    }
    size_t find(size_t x) {
        auto root = x;
        while (root != data[root]) {
            root = data[root];
        }
        while (x != root) {
            auto next = data[x];
            data[x] = root;
            x = next;
        }
        return root;
    }
    void merge(size_t x, size_t y) {
        x = find(x), y = find(y);
        if (x == y) {
            return;
        }
        if (rank[x] < rank[y]) {
            data[x] = y;
        } else if (rank[x] > rank[y]) {
            data[y] = x;
        } else {
            data[y] = x;
            rank[x]++;
        }
    }

private:
    std::vector<size_t> data;
    std::vector<uint8_t> rank;
};
