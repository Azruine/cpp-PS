/*==== Copyright 2025 Azruine ====*/

#include <iostream>
#include <utility>

using std::cin, std::cout;

namespace {
inline void fastio() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

#include <algorithm>
#include <complex>
#include <numbers>
#include <optional>
#include <vector>

namespace fft {
using complex = std::complex<double>;
using std::conj;
template <typename T>
    requires std::is_integral_v<T>
class FFT {
    size_t cache_size = 0;
    std::vector<complex> roots;
    constexpr static double PI = std::numbers::pi_v<double>;

    void fill_roots(size_t n) {
        if (n <= cache_size) {
            return;
        }
        cache_size = n;
        roots.resize(n >> 1);
        for (size_t i = 0; i < (n >> 1); i++) {
            double ang = 2.0 * PI * i / n;
            roots[i] = complex(std::cos(ang), std::sin(ang));
        }
    }

    void fft(std::vector<complex>& data, bool invert = false) {
        size_t n = data.size();
        if (n == 1) {
            return;
        }

        fill_roots(n);

        for (size_t i = 1, j = 0; i < n; i++) {
            size_t bit = n >> 1;
            for (; j & bit; bit >>= 1) {
                j ^= bit;
            }
            j ^= bit;
            if (i < j) {
                std::swap(data[i], data[j]);
            }
        }

        for (size_t k = 1; k < n; k <<= 1) {
            size_t step = cache_size / (k * 2);
            for (size_t i = 0; i < n; i += k * 2) {
                for (size_t j = 0; j < k; j++) {
                    complex w = roots[j * step];
                    if (invert) {
                        w = conj(w);
                    }
                    complex even = data[i + j];
                    complex odd = data[i + j + k] * w;
                    data[i + j] = even + odd;
                    data[i + j + k] = even - odd;
                }
            }
        }

        if (invert) {
            for (size_t i = 0; i < n; i++) {
                data[i] /= static_cast<double>(n);
            }
        }
    }

public:
    std::vector<T> multiply(std::vector<T> const& lhs,
                            std::vector<T> const& rhs) {
        if (lhs.size() == 0 || rhs.size() == 0) {
            return {};
        }
        constexpr size_t NAIVE_THRESHOLD = 64;
        if (lhs.size() * rhs.size() <= NAIVE_THRESHOLD * NAIVE_THRESHOLD) {
            std::vector<T> ret(lhs.size() + rhs.size() - 1, 0);
            for (size_t i = 0; i < lhs.size(); i++) {
                if (lhs[i] == 0) {
                    continue;
                }
                for (size_t j = 0; j < rhs.size(); j++) {
                    ret[i + j] += lhs[i] * rhs[j];
                }
            }
            return ret;
        }

        size_t result_size = lhs.size() + rhs.size() - 1;
        size_t n = 2;
        while (n < result_size) {
            n <<= 1;
        }

        std::vector<complex> pack(n);
        for (size_t i = 0; i < lhs.size(); i++) {
            pack[i].real(static_cast<double>(lhs[i]));
        }
        for (size_t i = 0; i < rhs.size(); i++) {
            pack[i].imag(static_cast<double>(rhs[i]));
        }

        std::vector<T> ret(result_size);

        fft(pack);
        for (size_t i = 0; i < n; i++) {
            pack[i] *= pack[i];
        }
        fft(pack, true);
        for (size_t i = 0; i < result_size; i++) {
            ret[i] = static_cast<T>(std::lround(pack[i].imag() * 0.5));
        }

        return ret;
    }
    std::vector<T> self_multiply(std::vector<T> const& vec) {
        if (vec.size() == 0) {
            return {};
        }
        size_t result_size = (2 * vec.size()) - 1;
        size_t n = 2;
        while (n < result_size) {
            n <<= 1;
        }
        std::vector<complex> fft_data(n);
        for (size_t i = 0; i < vec.size(); i++) {
            fft_data[i] = complex(static_cast<double>(vec[i]), 0.0);
        }
        fft(fft_data);
        for (size_t i = 0; i < n; i++) {
            fft_data[i] *= fft_data[i];
        }
        fft(fft_data, true);
        std::vector<T> result(result_size);
        for (size_t i = 0; i < result_size; i++) {
            result[i] = static_cast<T>(std::lround(fft_data[i].real()));
        }
        return result;
    }
};
};  // namespace fft

namespace ntt {
template <typename T>
class Barrett {
    T mod;
    __uint128_t m;

public:
    explicit Barrett(T mod_)
        : mod(mod_), m((static_cast<__uint128_t>(1) << 64) / mod) {}
    T reduce(__uint128_t x) const {
        T quotient = static_cast<T>((m * x) >> 64);
        T residue =
            static_cast<T>(x - (static_cast<__uint128_t>(quotient) * mod));
        return residue >= mod ? residue - mod : residue;
    }
    T reduce(T lhs, T rhs) const {
        __uint128_t x = static_cast<__uint128_t>(lhs) * rhs;
        return reduce(x);
    }
};

template <typename T>
class NTT {
    T mod;
    size_t cache_size = 0;
    Barrett<T> barrett;
    T primitive_root;
    std::vector<T> roots, inv_roots;

    void fill_roots(size_t n) {
        if (n <= cache_size) {
            return;
        }
        cache_size = n;
        roots.resize(n >> 1);
        inv_roots.resize(n >> 1);

        T w = power(primitive_root, (mod - 1) / n);
        T w_inv = power(w, mod - 2);

        roots[0] = inv_roots[0] = 1;

        for (size_t i = 1; i < (n >> 1); i++) {
            roots[i] = barrett.reduce(roots[i - 1], w);
            inv_roots[i] = barrett.reduce(inv_roots[i - 1], w_inv);
        }
    }

    T power(T base, T exp) const {
        T result = 1;
        while (exp > 0) {
            if (exp & 1) {
                result = barrett.reduce(result, base);
            }
            base = barrett.reduce(base, base);
            exp >>= 1;
        }
        return result;
    }

    T find_primitive_root() const {
        if (mod == 998244353 || mod == 469762049 || mod == 167772161) {
            return 3;
        }

        std::vector<T> factors;
        T phi = mod - 1;
        T n = phi;
        for (T i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                factors.push_back(i);
                while (n % i == 0) {
                    n /= i;
                }
            }
        }
        if (n > 1) {
            factors.push_back(n);
        }

        for (T i = 2; i < mod; i++) {
            bool is_primitive = true;
            for (T factor : factors) {
                if (power(i, phi / factor) == 1) {
                    is_primitive = false;
                    break;
                }
            }
            if (is_primitive) {
                return i;
            }
        }
        return 2;
    }

public:
    explicit NTT(T mod_)
        : mod(mod_), barrett(mod_), primitive_root(find_primitive_root()) {}

    void ntt(std::vector<T>& data, bool invert = false) {
        size_t n = data.size();
        if (n == 1) {
            return;
        }
        fill_roots(n);

        for (size_t i = 1, j = 0; i < n; i++) {
            size_t bit = n >> 1;
            for (; j & bit; bit >>= 1) {
                j ^= bit;
            }
            j ^= bit;
            if (i < j) {
                std::swap(data[i], data[j]);
            }
        }

        auto const& roots_table = invert ? inv_roots : roots;

        for (size_t k = 1; k < n; k <<= 1) {
            size_t step = cache_size / (k << 1);
            for (size_t i = 0; i < n; i += (k << 1)) {
                for (size_t j = 0; j < k; j++) {
                    T even = data[i + j];
                    T odd =
                        barrett.reduce(data[i + j + k], roots_table[j * step]);
                    data[i + j] =
                        (even + odd >= mod) ? even + odd - mod : even + odd;
                    data[i + j + k] =
                        (even >= odd) ? even - odd : even - odd + mod;
                }
            }
        }

        if (invert) {
            T n_inv = power(static_cast<T>(n), mod - 2);
            for (size_t i = 0; i < n; i++) {
                data[i] = barrett.reduce(data[i], n_inv);
            }
        }
    }

    std::vector<T> multiply(std::vector<T> const& lhs,
                            std::vector<T> const& rhs) {
        if (lhs.size() == 0 || rhs.size() == 0) {
            return {};
        }
        constexpr size_t NAIVE_THRESHOLD = 64;
        if (lhs.size() * rhs.size() <= NAIVE_THRESHOLD * NAIVE_THRESHOLD) {
            std::vector<T> ret(lhs.size() + rhs.size() - 1, 0);
            for (size_t i = 0; i < lhs.size(); i++) {
                if (lhs[i] == 0) {
                    continue;
                }
                for (size_t j = 0; j < rhs.size(); j++) {
                    ret[i + j] += lhs[i] * rhs[j];
                }
            }
            return ret;
        }
        size_t result_size = lhs.size() + rhs.size() - 1;
        size_t n = 2;
        while (n < result_size) {
            n <<= 1;
        }

        std::vector<T> lhs_ntt(n), rhs_ntt(n);
        for (size_t i = 0; i < lhs.size(); i++) {
            lhs_ntt[i] = lhs[i] % mod;
        }
        for (size_t i = 0; i < rhs.size(); i++) {
            rhs_ntt[i] = rhs[i] % mod;
        }

        ntt(lhs_ntt);
        ntt(rhs_ntt);

        for (size_t i = 0; i < n; i++) {
            lhs_ntt[i] = barrett.reduce(lhs_ntt[i], rhs_ntt[i]);
        }

        ntt(lhs_ntt, true);

        lhs_ntt.resize(result_size);
        return lhs_ntt;
    }
    std::vector<T> self_multiply(std::vector<T> const& vec) {
        if (vec.size() == 0) {
            return {};
        }
        size_t result_size = (2 * vec.size()) - 1;
        size_t n = 2;
        while (n < result_size) {
            n <<= 1;
        }

        std::vector<T> ntt_data(n);
        for (size_t i = 0; i < vec.size(); i++) {
            ntt_data[i] = vec[i] % mod;
        }

        ntt(ntt_data);

        for (size_t i = 0; i < n; i++) {
            ntt_data[i] = barrett.reduce(ntt_data[i], ntt_data[i]);
        }

        ntt(ntt_data, true);

        ntt_data.resize(result_size);
        return ntt_data;
    }
};
};  // namespace ntt

struct Node {
    int32_t low = 0, high = 0;
    int32_t split = 0;
    int32_t depth = 0;
    int32_t sub_size = 0;
    size_t leftmost_leaf_idx, rightmost_leaf_idx;
    std::optional<size_t> parent;
    std::optional<size_t> l_child, r_child;
    std::optional<size_t> heavy_child;

    bool is_leaf() const { return !l_child; }
};

class IntervalTree {
    size_t n = 0;
    std::vector<int32_t> splits;
    std::vector<size_t> leaf_idx;
    size_t split_idx = 0;
    std::vector<Node> nodes;
    size_t build(int32_t low_init, int32_t high_init,
                 std::optional<size_t> parent_init, int32_t depth_init) {
        struct Frame {
            int32_t low, high;
            std::optional<size_t> parent;
            int32_t depth;
            size_t self_idx;
            int phase;
            size_t left_child_idx;
            size_t right_child_idx;
        };

        std::vector<Frame> stack;
        stack.reserve(64);
        stack.emplace_back(low_init, high_init, parent_init, depth_init, 0, 0,
                           0, 0);

        size_t root_idx = SIZE_MAX;

        auto finish_node = [&](size_t my_idx) {
            stack.pop_back();
            if (stack.empty()) {
                root_idx = my_idx;
            } else {
                Frame& frame = stack.back();
                if (frame.phase == 1) {
                    frame.left_child_idx = my_idx;
                } else {
                    frame.right_child_idx = my_idx;
                }
            }
        };

        while (!stack.empty()) {
            Frame& frame = stack.back();

            if (frame.phase == 0) {
                frame.self_idx = nodes.size();
                nodes.emplace_back();
                nodes[frame.self_idx].low = frame.low;
                nodes[frame.self_idx].high = frame.high;
                nodes[frame.self_idx].parent = frame.parent;
                nodes[frame.self_idx].depth = frame.depth;

                if (frame.low == frame.high) {
                    nodes[frame.self_idx].sub_size = 1;
                    leaf_idx[frame.low] = frame.self_idx;
                    nodes[frame.self_idx].leftmost_leaf_idx = frame.self_idx;
                    nodes[frame.self_idx].rightmost_leaf_idx = frame.self_idx;
                    finish_node(frame.self_idx);
                    continue;
                }

                int32_t m = splits[split_idx++];
                nodes[frame.self_idx].split = m;
                frame.phase = 1;
                stack.emplace_back(frame.low, m, frame.self_idx,
                                   frame.depth + 1, 0, 0, 0, 0);
            } else if (frame.phase == 1) {
                frame.phase = 2;
                int32_t m = nodes[frame.self_idx].split;
                stack.emplace_back(m + 1, frame.high, frame.self_idx,
                                   frame.depth + 1, 0, 0, 0, 0);
            } else {
                size_t left = frame.left_child_idx;
                size_t right = frame.right_child_idx;
                size_t my_idx = frame.self_idx;
                nodes[my_idx].l_child = left;
                nodes[my_idx].r_child = right;
                nodes[my_idx].sub_size =
                    nodes[left].sub_size + nodes[right].sub_size;
                nodes[my_idx].heavy_child =
                    (nodes[left].sub_size >= nodes[right].sub_size) ? left
                                                                    : right;
                nodes[my_idx].leftmost_leaf_idx = nodes[left].leftmost_leaf_idx;
                nodes[my_idx].rightmost_leaf_idx =
                    nodes[right].rightmost_leaf_idx;
                finish_node(my_idx);
            }
        }

        return root_idx;
    }

public:
    void build(size_t n_, std::vector<int32_t> splits_) {
        n = n_;
        splits = std::move(splits_);
        split_idx = 0;
        nodes.clear();
        nodes.reserve(n << 1);
        leaf_idx.assign(n + 1, 0);
        if (n > 0) {
            build(1, as<int32_t>(n), std::nullopt, 0);
        }
    }
    Node const& operator[](size_t index) const { return nodes[index]; }
    size_t size() const { return n; }
    size_t node_size() const { return nodes.size(); }
    size_t leaf(int32_t x) const { return leaf_idx[x]; }
};

class Solver {
    using poly = std::vector<int64_t>;

    std::vector<int32_t> queries;
    std::vector<poly> a, b;
    fft::FFT<int64_t> fft;
    // ntt::NTT<int64_t> fft{998244353};

    std::vector<bool> visited;
    std::vector<size_t> subtree_size;

    struct ComputeSizeFrame {
        size_t v;
        std::optional<size_t> from;
        int phase;
    };
    std::vector<ComputeSizeFrame> compute_size_stack;

    std::optional<IntervalTree> read() {
        IntervalTree tree;

        size_t n = 0;
        size_t query_cnt = 0;
        if (!(cin >> n >> query_cnt)) {
            return std::nullopt;
        }
        std::vector<int32_t> splits(n - 1);
        for (auto& split : splits) {
            cin >> split;
        }
        tree.build(n, std::move(splits));
        queries.assign(query_cnt, 0);
        for (auto& query : queries) {
            cin >> query;
        }

        return tree;
    }

    static void poly_trim(poly& poly) {
        while (!poly.empty() && poly.back() == 0) {
            poly.pop_back();
        }
    }

    static void poly_add(poly& dst, poly const& src) {
        if (dst.size() < src.size()) {
            dst.resize(src.size(), 0);
        }
        for (size_t i = 0; i < src.size(); i++) {
            dst[i] += src[i];
        }
        poly_trim(dst);
    }

    static void poly_add_shifted(poly& dst, poly const& src, size_t shift) {
        if (dst.size() < src.size() + shift) {
            dst.resize(src.size() + shift, 0);
        }
        for (size_t i = 0; i < src.size(); i++) {
            dst[i + shift] += src[i];
        }
        poly_trim(dst);
    }

    static void poly_add_monomial(poly& dst, size_t deg, int64_t value) {
        if (dst.size() <= deg) {
            dst.resize(deg + 1, 0);
        }
        dst[deg] += value;
        poly_trim(dst);
    }
    static void shifted_poly_add(size_t& dst_shift, poly& dst_body,
                                 size_t src_shift, poly const& src_body) {
        if (src_body.empty()) {
            return;
        }
        if (dst_body.empty()) {
            dst_shift = src_shift;
            dst_body = src_body;
            return;
        }

        size_t new_shift = std::min(dst_shift, src_shift);
        size_t dst_pad = dst_shift - new_shift;
        size_t src_pad = src_shift - new_shift;

        size_t result_size =
            std::max(dst_pad + dst_body.size(), src_pad + src_body.size());

        poly result(result_size, 0);
        for (size_t i = 0; i < dst_body.size(); i++) {
            result[i + dst_pad] += dst_body[i];
        }
        for (size_t i = 0; i < src_body.size(); i++) {
            result[i + src_pad] += src_body[i];
        }

        dst_shift = new_shift;
        dst_body = std::move(result);
    }

    void dc_compute_size(IntervalTree const& tree, size_t start,
                         std::optional<size_t> initial_from) {
        compute_size_stack.clear();
        compute_size_stack.emplace_back(start, initial_from, 0);

        while (!compute_size_stack.empty()) {
            size_t v = compute_size_stack.back().v;
            auto from = compute_size_stack.back().from;
            int phase = compute_size_stack.back().phase;

            auto const& node = tree[v];

            if (phase == 0) {
                subtree_size[v] = 1;
                compute_size_stack.back().phase = 1;

                auto try_push = [&](std::optional<size_t> node_idx) {
                    if (!node_idx.has_value()) {
                        return;
                    }
                    if (visited[node_idx.value()]) {
                        return;
                    }
                    if (from && node_idx.value() == from.value()) {
                        return;
                    }
                    compute_size_stack.emplace_back(node_idx.value(), v, 0);
                };
                try_push(node.parent);
                try_push(node.l_child);
                try_push(node.r_child);
            } else {
                auto try_add = [&](std::optional<size_t> node_idx) {
                    if (!node_idx.has_value()) {
                        return;
                    }
                    if (visited[node_idx.value()]) {
                        return;
                    }
                    if (from && node_idx.value() == from.value()) {
                        return;
                    }
                    subtree_size[v] += subtree_size[node_idx.value()];
                };
                try_add(node.parent);
                try_add(node.l_child);
                try_add(node.r_child);

                compute_size_stack.pop_back();
            }
        }
    }
    size_t dc_find_centroid(IntervalTree const& tree, size_t start,
                            size_t total) {
        size_t v = start;
        std::optional<size_t> from = std::nullopt;

        while (true) {
            auto const& node = tree[v];

            auto check_move =
                [&](std::optional<size_t> node_idx) -> std::optional<size_t> {
                if (!node_idx.has_value()) {
                    return std::nullopt;
                }
                if (visited[node_idx.value()]) {
                    return std::nullopt;
                }
                if (from && node_idx.value() == from.value()) {
                    return std::nullopt;
                }
                if (subtree_size[node_idx.value()] * 2 > total) {
                    return node_idx;
                }
                return std::nullopt;
            };

            std::optional<size_t> next;
            if ((next = check_move(node.parent))
                || (next = check_move(node.l_child))
                || (next = check_move(node.r_child))) {
                from = v;
                v = next.value();
                continue;
            }

            return v;
        }
    }

    enum class Dir { LEFT, RIGHT };

    // Chain link transition under D&C:
    //   A_v_low = C_A · A_v_high + D_A     (a-side polynomial recurrence)
    //   B_v_low = C_B · B_v_high + D_B     (b-side polynomial recurrence)
    // E: case_A contributions, accumulated as z^{E_shift} · E_body
    // F_A: a-side chain ascent, z^{F_A_shift} · F_A_body
    // F_B: b-side chain ascent, z^{F_B_shift} · F_B_body
    struct ChainInfo {
        poly C_A, D_A, C_B, D_B;

        size_t E_shift;
        poly E_body;

        size_t F_A_shift;
        poly F_A_body;

        size_t F_B_shift;
        poly F_B_body;
    };
    ChainInfo dc_chain_base(IntervalTree const& tree, size_t v, Dir dir) {
        auto const& node = tree[v];
        int32_t depth = node.depth;

        size_t bar;
        if (dir == Dir::LEFT) {
            bar = node.r_child.value();
        } else {
            bar = node.l_child.value();
        }

        poly a_bar = compute_a_V(tree, bar);
        poly b_bar = compute_b_V(tree, bar);
        ChainInfo info;

        if (dir == Dir::LEFT) {
            info.C_A = {0, 0, 1};
            poly_add_shifted(info.D_A, a_bar, 1);
            poly_add_monomial(info.D_A, 1, 1);
            poly_add_monomial(info.D_A, 3, -1);
        } else {
            info.C_A = {0, 1};
            poly_add_shifted(info.D_A, a_bar, 2);
            poly_add_monomial(info.D_A, 1, 1);
            poly_add_monomial(info.D_A, 3, -1);
        }

        if (dir == Dir::LEFT) {
            info.C_B = {0, 1};
            poly_add_shifted(info.D_B, b_bar, 2);
            poly_add_monomial(info.D_B, 1, 1);
            poly_add_monomial(info.D_B, 3, -1);
        } else {
            info.C_B = {0, 0, 1};
            poly_add_shifted(info.D_B, b_bar, 1);
            poly_add_monomial(info.D_B, 1, 1);
            poly_add_monomial(info.D_B, 3, -1);
        }

        info.E_shift = 0;
        info.E_body = {};
        bool case_A = !visited[node.leftmost_leaf_idx]
                      && !visited[node.rightmost_leaf_idx];
        size_t shift = as<size_t>(depth) + 1;

        if (case_A) {
            info.E_shift = shift;
            info.E_body = {1, 0, -1};
        }

        info.F_A_shift = 0;
        info.F_A_body = {};
        info.F_B_shift = 0;
        info.F_B_body = {};

        if (dir == Dir::LEFT) {
            info.F_A_shift = shift;
            info.F_A_body = b_bar;
        } else {
            info.F_B_shift = shift;
            info.F_B_body = a_bar;
        }

        return info;
    }

    ChainInfo dc_chain_merge(ChainInfo const& left, ChainInfo const& right) {
        ChainInfo result;

        result.C_A = fft.multiply(left.C_A, right.C_A);
        result.D_A = fft.multiply(left.C_A, right.D_A);
        poly_add(result.D_A, left.D_A);

        result.C_B = fft.multiply(left.C_B, right.C_B);
        result.D_B = fft.multiply(left.C_B, right.D_B);
        poly_add(result.D_B, left.D_B);

        result.E_shift = left.E_shift;
        result.E_body = left.E_body;

        if (!left.F_A_body.empty()) {
            poly fa_da_product = fft.multiply(left.F_A_body, right.D_A);
            shifted_poly_add(result.E_shift, result.E_body, left.F_A_shift,
                             fa_da_product);
        }

        if (!left.F_B_body.empty()) {
            poly fb_db_product = fft.multiply(left.F_B_body, right.D_B);
            shifted_poly_add(result.E_shift, result.E_body, left.F_B_shift,
                             fb_db_product);
        }

        shifted_poly_add(result.E_shift, result.E_body, right.E_shift,
                         right.E_body);

        if (left.F_A_body.empty()) {
            result.F_A_body = {};
            result.F_A_shift = 0;
        } else {
            result.F_A_body = fft.multiply(left.F_A_body, right.C_A);
            result.F_A_shift = left.F_A_shift;
        }
        shifted_poly_add(result.F_A_shift, result.F_A_body, right.F_A_shift,
                         right.F_A_body);

        if (left.F_B_body.empty()) {
            result.F_B_body = {};
            result.F_B_shift = 0;
        } else {
            result.F_B_body = fft.multiply(left.F_B_body, right.C_B);
            result.F_B_shift = left.F_B_shift;
        }
        shifted_poly_add(result.F_B_shift, result.F_B_body, right.F_B_shift,
                         right.F_B_body);

        return result;
    }
    ChainInfo dc_chain_divide(IntervalTree const& tree,
                              std::vector<size_t> const& chain,
                              std::vector<Dir> const& chain_dir, size_t low,
                              size_t high, int depth = 0) {
        if (high - low == 1) {
            return dc_chain_base(tree, chain[low], chain_dir[low]);
        }
        size_t mid = (low + high) / 2;
        auto left =
            dc_chain_divide(tree, chain, chain_dir, low, mid, depth + 1);
        auto right =
            dc_chain_divide(tree, chain, chain_dir, mid, high, depth + 1);
        auto result = dc_chain_merge(left, right);
        return result;
    }

    poly compute_a_V(IntervalTree const& tree, size_t v) {
        poly result;
        size_t cur = v;
        size_t total_shift = 0;

        while (true) {
            auto const& node = tree[cur];
            if (node.is_leaf()) {
                poly_add_monomial(result, total_shift + 1, 1);
                break;
            }

            size_t heavy = node.heavy_child.value();
            size_t light = (heavy == node.l_child.value())
                               ? node.r_child.value()
                               : node.l_child.value();

            poly light_poly = compute_a_V(tree, light);

            size_t heavy_shift, light_shift;
            if (heavy == node.l_child.value()) {
                heavy_shift = 2;
                light_shift = 1;
            } else {
                heavy_shift = 1;
                light_shift = 2;
            }

            for (size_t i = 0; i < light_poly.size(); i++) {
                poly_add_monomial(result, total_shift + light_shift + i,
                                  light_poly[i]);
            }

            if (!visited[node.leftmost_leaf_idx]) {
                poly_add_monomial(result, total_shift + 1, 1);
                poly_add_monomial(result, total_shift + 3, -1);
            }

            total_shift += heavy_shift;
            cur = heavy;
        }

        poly_trim(result);
        return result;
    }
    poly compute_b_V(IntervalTree const& tree, size_t v) {
        poly result;
        size_t cur = v;
        size_t total_shift = 0;

        while (true) {
            auto const& node = tree[cur];
            if (node.is_leaf()) {
                poly_add_monomial(result, total_shift + 1, 1);
                break;
            }

            size_t heavy = node.heavy_child.value();
            size_t light = (heavy == node.l_child.value())
                               ? node.r_child.value()
                               : node.l_child.value();

            poly light_poly = compute_b_V(tree, light);

            size_t heavy_shift, light_shift;
            if (heavy == node.l_child.value()) {
                heavy_shift = 1;
                light_shift = 2;
            } else {
                heavy_shift = 2;
                light_shift = 1;
            }

            for (size_t i = 0; i < light_poly.size(); i++) {
                poly_add_monomial(result, total_shift + light_shift + i,
                                  light_poly[i]);
            }

            if (!visited[node.rightmost_leaf_idx]) {
                poly_add_monomial(result, total_shift + 1, 1);
                poly_add_monomial(result, total_shift + 3, -1);
            }

            total_shift += heavy_shift;
            cur = heavy;
        }

        poly_trim(result);
        return result;
    }

    void dc_solve(IntervalTree const& tree, std::vector<int64_t>& result,
                  size_t start) {
        if (visited[start]) {
            return;
        }

        dc_compute_size(tree, start, std::nullopt);
        size_t total = subtree_size[start];

        if (total == 1) {
            size_t k = as<size_t>(tree[start].depth) + 1;
            if (k < result.size()) {
                result[k] += 1;
            }
            visited[start] = true;
            return;
        }
        // centroid
        size_t G = dc_find_centroid(tree, start, total);

        std::vector<size_t> chain;
        std::vector<Dir> chain_dir;
        {
            size_t cur = G;
            while (true) {
                chain.push_back(cur);
                if (cur == start) {
                    break;
                }
                cur = tree[cur].parent.value();
            }
            std::ranges::reverse(chain);
            for (size_t i = 0; i + 1 < chain.size(); i++) {
                auto const& node = tree[chain[i]];
                if (node.l_child.has_value()
                    && node.l_child.value()
                    == chain[i + 1]) {
                    chain_dir.push_back(Dir::LEFT);
                } else {
                    chain_dir.push_back(Dir::RIGHT);
                }
            }
        }
        size_t k = chain.size();
        {
            auto const& g_node = tree[G];
            size_t shift = as<size_t>(g_node.depth) + 1;
            poly aG, bG;

            if (g_node.is_leaf()) {
                if (shift < result.size()) {
                    result[shift] += 1;
                }
                aG = {0, 1};
                bG = {0, 1};
            } else {
                size_t left = g_node.l_child.value();
                size_t right = g_node.r_child.value();
                poly al_G = compute_a_V(tree, left);
                poly ar_G = compute_a_V(tree, right);
                poly bl_G = compute_b_V(tree, left);
                poly br_G = compute_b_V(tree, right);

                poly prod = (al_G.empty() || br_G.empty())
                                ? poly{}
                                : fft.multiply(al_G, br_G);
                for (size_t i = 0; i < prod.size(); i++) {
                    if (i + shift < result.size()) {
                        result[i + shift] += prod[i];
                    }
                }
                bool case_A = !visited[g_node.leftmost_leaf_idx]
                              && !visited[g_node.rightmost_leaf_idx];
                if (case_A) {
                    if (shift < result.size()) {
                        result[shift] += 1;
                    }
                    if (shift + 2 < result.size()) {
                        result[shift + 2] -= 1;
                    }
                }

                poly_add_shifted(aG, al_G, 2);
                poly_add_shifted(aG, ar_G, 1);
                if (!visited[g_node.leftmost_leaf_idx]) {
                    poly_add_monomial(aG, 1, 1);
                    poly_add_monomial(aG, 3, -1);
                }
                poly_add_shifted(bG, bl_G, 1);
                poly_add_shifted(bG, br_G, 2);
                if (!visited[g_node.rightmost_leaf_idx]) {
                    poly_add_monomial(bG, 1, 1);
                    poly_add_monomial(bG, 3, -1);
                }
            }

            if (k >= 2) {
                ChainInfo info =
                    dc_chain_divide(tree, chain, chain_dir, 0, k - 1);

                poly contrib;
                size_t contrib_shift = 0;

                if (!info.E_body.empty()) {
                    contrib_shift = info.E_shift;
                    contrib = info.E_body;
                }

                if (!info.F_A_body.empty() && !aG.empty()) {
                    poly product = fft.multiply(info.F_A_body, aG);
                    shifted_poly_add(contrib_shift, contrib, info.F_A_shift,
                                     product);
                }

                if (!info.F_B_body.empty() && !bG.empty()) {
                    poly product = fft.multiply(info.F_B_body, bG);
                    shifted_poly_add(contrib_shift, contrib, info.F_B_shift,
                                     product);
                }

                for (size_t i = 0; i < contrib.size(); i++) {
                    size_t idx = i + contrib_shift;
                    if (idx < result.size()) {
                        result[idx] += contrib[i];
                    }
                }
            }
        }

        for (size_t v : chain) {
            visited[v] = true;
        }

        for (size_t v : chain) {
            auto const& node = tree[v];
            auto try_recurse = [&](std::optional<size_t> node_idx) {
                if (node_idx && !visited[node_idx.value()]) {
                    dc_solve(tree, result, node_idx.value());
                }
            };
            try_recurse(node.l_child);
            try_recurse(node.r_child);
        }
    }

    std::vector<int64_t> fill_result_centroid(IntervalTree const& tree) {
        size_t n = tree.size();
        std::vector<int64_t> ret((n << 1) + 1, 0);
        if (n == 0) {
            return ret;
        }
        visited.assign(tree.node_size(), false);
        subtree_size.assign(tree.node_size(), 0);
        dc_solve(tree, ret, 0);

        return ret;
    }

public:
    void solve() {
        while (auto tree = read()) {
            auto centroid_result = fill_result_centroid(tree.value());
            for (auto const& query : queries) {
                if (query >= 0 && as<size_t>(query) < centroid_result.size()) {
                    cout << centroid_result[query] << '\n';
                } else {
                    cout << 0 << '\n';
                }
            }
        }
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
