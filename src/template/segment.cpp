/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <cstdint>
#include <vector>
class SegTree {
private:
    static constexpr size_t height_multiplier = 8;
    size_t height;
    size_t size;
    std::vector<int> data;
    std::vector<int> delay;

public:
    void init(int n) {
        size = static_cast<size_t>(n);
        height =
            sizeof(int) * height_multiplier -
            static_cast<size_t>(__builtin_clz(static_cast<uint32_t>(size)));
        data.assign(size << 1, 0);
        delay.assign(size, 0);
    }
    void apply(size_t pos, int value) {
        data[pos] += value;
        if (pos < size) {
            delay[pos] = value;
        }
    }
    void build(size_t pos) {
        while (pos > 1) {
            pos >>= 1;
            data[pos] = data[pos << 1] + data[pos << 1 | 1] + delay[pos];
        }
    }
    void push(size_t pos) {
        for (size_t sz_t = height; sz_t > 0; --sz_t) {
            auto i = pos >> sz_t;
            if (delay[i] != 0) {
                apply(i << 1, delay[i]);
                apply(i << 1 | 1, delay[i]);
                delay[i] = 0;
            }
        }
    }
    void increase(size_t left, size_t right, int value) {
        left += size, right += size;
        auto left0 = left;
        auto right0 = right;
        for (; left < right; left >>= 1, right >>= 1) {
            if (left & 1) {
                apply(left++, value);
            }
            if (right & 1) {
                apply(--right, value);
            }
        }
        build(left0);
        build(right0 - 1);
    }
    int query(size_t left, size_t right) {
        left += size, right += size;
        push(left);
        push(right - 1);
        int res = 0;
        for (; left < right; left >>= 1, right >>= 1) {
            if (left & 1) {
                res += data[left++];
            }
            if (right & 1) {
                res += data[--right];
            }
        }
        return res;
    }
};

class SegTreeMax {
private:
    static constexpr size_t height_multiplier = 8;
    size_t height;
    size_t size;
    std::vector<int> tree;
    std::vector<int> delay;

public:
    void init(size_t n) {
        size = n;
        height =
            sizeof(int) * height_multiplier -
            static_cast<size_t>(__builtin_clz(static_cast<uint32_t>(size)));
        tree.resize(2 * n, 0);
        delay.resize(n, 0);
    }
    void buildAll() {
        for (auto i = size - 1; i > 0; i--) {
            tree[i] = std::max(tree[i << 1], tree[i << 1 | 1]);
        }
    }
    void setLeaf(std::vector<int>& nums) {
        for (size_t i = 0; i < size; i++) {
            tree[size + i] = nums[i];
        }
    }
    void apply(size_t pos, int value) {
        tree[pos] += value;
        if (pos < size) {
            delay[pos] += value;
        }
    }
    void build(size_t pos) {
        while (pos > 1) {
            pos >>= 1;
            tree[pos] =
                std::max(tree[pos << 1], tree[pos << 1 | 1]) + delay[pos];
        }
    }
    void push(size_t pos) {
        for (size_t sz_ = height; sz_ > 0; sz_--) {
            auto i = pos >> sz_;
            if (delay[i] != 0) {
                apply(i << 1, delay[i]);
                apply(i << 1 | 1, delay[i]);
                delay[i] = 0;
            }
        }
    }
    void increase(size_t left, size_t right, int value) {
        left += size, right += size;
        auto left0 = left;
        auto right0 = right;
        for (; left < right; left >>= 1, right >>= 1) {
            if (left & 1) {
                apply(left++, value);
            }
            if (right & 1) {
                apply(--right, value);
            }
        }
        build(left0);
        build(right0 - 1);
    }
    int query(size_t left, size_t right) {
        left += size, right += size;
        push(left);
        push(right - 1);
        int res = INT32_MIN;
        for (; left < right; left >>= 1, right >>= 1) {
            if (left & 1) {
                res = std::max(res, tree[left++]);
            }
            if (right & 1) {
                res = std::max(res, tree[--right]);
            }
        }
        return res;
    }
};
