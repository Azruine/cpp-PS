/*==== Copyright 2025 Azruine ====*/
#pragma once

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <limits>
#include <utility>
#include <vector>

// Op may provide static functions or const member functions.
template <typename Op, typename T>
concept SegmentOp = requires(Op const& op, T const& lhs, T const& rhs) {
    { op.identity } -> std::convertible_to<T>;
    { op.combine(lhs, rhs) } -> std::same_as<T>;
};

template <typename Op, typename T>
concept LazySegmentOp =
    SegmentOp<Op, T>
    && requires(Op const& op, T& node, typename Op::lazy_type const& old_tag,
                Op::lazy_type const& new_tag, std::size_t len) {
           { op.lazy_identity } -> std::convertible_to<typename Op::lazy_type>;
           { old_tag == new_tag } -> std::convertible_to<bool>;
           { op.apply(node, new_tag, len) } -> std::same_as<void>;
           {
               op.compose(old_tag, new_tag)
           } -> std::same_as<typename Op::lazy_type>;
       };

namespace seg_detail {
template <typename Op, typename T, bool = LazySegmentOp<Op, T>>
struct LazyStorage {
    // Placeholder for signatures; range updates are constrained away.
    struct tag_type {};
};

template <typename Op, typename T>
struct LazyStorage<Op, T, true> {
    using tag_type = Op::lazy_type;
    std::vector<tag_type> tags;
};
}  // namespace seg_detail

// combine must be associative, with identity as a two-sided identity.
// compose(old_tag, new_tag) applies old_tag first, then new_tag.
// apply must respect combine, segment lengths, and tag composition.
// Public positions/ranges must lie in [0, length]; ranges are half-open.
// Arithmetic must remain representable in the operation's numeric types.
template <typename T, SegmentOp<T> Op>
class SegTree {
    static constexpr bool has_lazy = LazySegmentOp<Op, T>;
    using Storage = seg_detail::LazyStorage<Op, T>;
    using Tag = Storage::tag_type;

    [[no_unique_address]] Op op{};
    [[no_unique_address]] Storage lazy{};
    std::size_t length = 0;
    std::size_t size = 1;
    std::size_t height = 0;
    std::vector<T> tree;

    void apply(std::size_t pos, Tag const& value, std::size_t len)
        requires has_lazy
    {
        op.apply(tree[pos], value, len);
        if (pos < size) {
            lazy.tags[pos] = op.compose(lazy.tags[pos], value);
        }
    }

    void build(std::size_t pos) {
        std::size_t len = 2;
        while (pos > 1) {
            pos >>= 1;
            tree[pos] = op.combine(tree[pos << 1], tree[pos << 1 | 1]);
            if constexpr (has_lazy) {
                if (!(lazy.tags[pos] == op.lazy_identity)) {
                    op.apply(tree[pos], lazy.tags[pos], len);
                }
            }
            len <<= 1;
        }
    }

    void push(std::size_t pos) {
        if constexpr (has_lazy) {
            for (std::size_t level = height; level > 0; --level) {
                std::size_t parent = pos >> level;
                if (lazy.tags[parent] == op.lazy_identity) {
                    continue;
                }
                std::size_t child_len = std::size_t{1} << (level - 1);
                apply(parent << 1, lazy.tags[parent], child_len);
                apply(parent << 1 | 1, lazy.tags[parent], child_len);
                lazy.tags[parent] = op.lazy_identity;
            }
        }
    }

public:
    void init(std::size_t n, Op operation = {}) {
        op = std::move(operation);
        length = n;
        size = 1;
        height = 0;
        while (size < length) {
            size <<= 1;
            ++height;
        }
        tree.assign(size << 1, op.identity);
        if constexpr (has_lazy) {
            lazy.tags.assign(size, op.lazy_identity);
        }
    }

    // Initialization only: call after init(), before updates.
    void set_leaf(std::vector<T> const& nums) {
        for (std::size_t i = 0; i < std::min(length, nums.size()); ++i) {
            tree[size + i] = nums[i];
        }
    }

    // Initialization only: call after set_leaf().
    void build_all() {
        for (std::size_t i = size - 1; i > 0; --i) {
            tree[i] = op.combine(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    // Kept under the original name; value is an Op-defined update tag.
    void increase(std::size_t left, std::size_t right, Tag const& value)
        requires has_lazy
    {
        if (left >= right) {
            return;
        }
        left += size;
        right += size;
        std::size_t left0 = left;
        std::size_t right0 = right;
        push(left0);
        push(right0 - 1);
        std::size_t len = 1;
        for (; left < right; left >>= 1, right >>= 1, len <<= 1) {
            if (left & 1) {
                apply(left++, value, len);
            }
            if (right & 1) {
                apply(--right, value, len);
            }
        }
        build(left0);
        build(right0 - 1);
    }

    void set(std::size_t pos, T const& value) {
        pos += size;
        push(pos);
        tree[pos] = value;
        build(pos);
    }

    T query(std::size_t left, std::size_t right) {
        if (left >= right) {
            return op.identity;
        }
        left += size;
        right += size;
        push(left);
        push(right - 1);
        T lhs = op.identity;
        T rhs = op.identity;
        for (; left < right; left >>= 1, right >>= 1) {
            if (left & 1) {
                lhs = op.combine(lhs, tree[left++]);
            }
            if (right & 1) {
                rhs = op.combine(tree[--right], rhs);
            }
        }
        return op.combine(lhs, rhs);
    }
};

// Non-lazy operations.
template <typename T>
struct SumOp {
    static constexpr T identity = T{};
    static T combine(T const& lhs, T const& rhs) { return lhs + rhs; }
};

template <typename T>
struct MaxOp {
    static constexpr T identity = std::numeric_limits<T>::lowest();
    static T combine(T const& lhs, T const& rhs) { return std::max(lhs, rhs); }
};

template <typename T>
struct MinOp {
    static constexpr T identity = std::numeric_limits<T>::max();
    static T combine(T const& lhs, T const& rhs) { return std::min(lhs, rhs); }
};

// Common tag type/composition for range addition.
template <typename T>
struct AddTag {
    using lazy_type = T;
    static constexpr T lazy_identity = T{};
    static T compose(T const& old_tag, T const& new_tag) {
        return old_tag + new_tag;
    }
};

// Lazy operations reuse the corresponding non-lazy combine/identity.
template <typename T>
struct LazySumOp : SumOp<T>, AddTag<T> {
    static void apply(T& node, T const& tag, std::size_t len) {
        node += tag * static_cast<T>(len);
    }
};

template <typename T>
struct LazyMaxOp : MaxOp<T>, AddTag<T> {
    static void apply(T& node, T const& tag, std::size_t /*len*/) {
        node += tag;
    }
};

template <typename T>
struct LazyMinOp : MinOp<T>, AddTag<T> {
    static void apply(T& node, T const& tag, std::size_t /*len*/) {
        node += tag;
    }
};
