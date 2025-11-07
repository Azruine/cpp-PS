/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <cstdint>
#include <limits>
#include <vector>

template <typename T>
struct SumOp {
    static constexpr T identity = 0;
    static T combine(const T& lhs, const T& rhs) { return lhs + rhs; }
    static void apply(T& node, const T& lazy) { node += lazy; }
};

template <typename T>
struct MaxOp {
    static constexpr T identity = std::numeric_limits<T>::min();
    static T combine(const T& lhs, const T& rhs) { return std::max(lhs, rhs); }
    static void apply(T& node, const T& lazy) { node += lazy; }
};

template <typename T>
struct MinOp {
    static constexpr T identity = std::numeric_limits<T>::max();
    static T combine(const T& lhs, const T& rhs) { return std::min(lhs, rhs); }
    static void apply(T& node, const T& lazy) { node += lazy; }
};

template <typename T, typename Op>
class LazySegTree {
private:
    static constexpr size_t height_multiplier = 8;
    size_t height;
    size_t size;
    std::vector<T> tree;
    std::vector<T> lazy;

    void apply(size_t pos, T value) {
        Op::apply(tree[pos], value);
        if (pos < size) {
            Op::apply(lazy[pos], value);
        }
    }

    void build(size_t pos) {
        while (pos > 1) {
            pos >>= 1;
            tree[pos] = Op::combine(tree[pos << 1], tree[pos << 1 | 1]);
            if (pos < size) {
                Op::apply(tree[pos], lazy[pos]);
            }
        }
    }

    void push(size_t pos) {
        for (size_t sz = height; sz > 0; --sz) {
            size_t i = pos >> sz;
            if (lazy[i] != 0) {
                apply(i << 1, lazy[i]);
                apply(i << 1 | 1, lazy[i]);
                lazy[i] = 0;
            }
        }
    }

public:
    void init(size_t n) {
        size = n;
        height =
            sizeof(int) * height_multiplier -
            static_cast<size_t>(__builtin_clz(static_cast<uint32_t>(size)));
        tree.assign(size << 1, Op::identity);
        lazy.assign(size, 0);
    }

    void setLeaf(std::vector<T> const& nums) {
        for (size_t i = 0; i < std::min(size, nums.size()); i++) {
            tree[size + i] = nums[i];
        }
    }

    void read_leaf() {
        for (size_t i = 0; i < size; i++) {
            std::cin >> tree[size + i];
        }
    }

    void build_all() {
        for (size_t i = size - 1; i > 0; --i) {
            tree[i] = Op::combine(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    void increase(size_t left, size_t right, T value) {
        left += size;
        right += size;
        size_t left0 = left;
        size_t right0 = right;

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

    T query(size_t left, size_t right) {
        left += size;
        right += size;
        push(left);
        push(right - 1);

        T res = Op::identity;
        for (; left < right; left >>= 1, right >>= 1) {
            if (left & 1) {
                res = Op::combine(res, tree[left++]);
            }
            if (right & 1) {
                res = Op::combine(res, tree[--right]);
            }
        }
        return res;
    }
};

using SegTreeSum = LazySegTree<int, SumOp<int>>;
using SegTreeMax = LazySegTree<int, MaxOp<int>>;
using SegTreeMin = LazySegTree<int, MinOp<int>>;
