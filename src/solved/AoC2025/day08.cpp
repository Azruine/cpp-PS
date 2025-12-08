/*==== Copyright 2025 Azruine ====*/

#include <iostream>
#include <type_traits>
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

template <typename T>
class iota_iterator {
    T current_;
    T step_;

public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    explicit constexpr iota_iterator(T current, T step = T{1}) noexcept
        : current_(current), step_(step) {}

    constexpr T operator*() const noexcept { return current_; }
    constexpr const T* operator->() const noexcept { return &current_; }

    constexpr iota_iterator& operator++() noexcept {
        current_ += step_;
        return *this;
    }
    constexpr iota_iterator operator++(int) noexcept {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    constexpr iota_iterator& operator--() noexcept {
        current_ -= step_;
        return *this;
    }
    constexpr iota_iterator operator--(int) noexcept {
        auto tmp = *this;
        --(*this);
        return tmp;
    }

    constexpr iota_iterator& operator+=(difference_type n) noexcept {
        current_ += step_ * static_cast<T>(n);
        return *this;
    }
    constexpr iota_iterator& operator-=(difference_type n) noexcept {
        current_ -= step_ * static_cast<T>(n);
        return *this;
    }

    constexpr iota_iterator operator+(difference_type n) const noexcept {
        return iota_iterator(current_ + (step_ * static_cast<T>(n)), step_);
    }
    constexpr iota_iterator operator-(difference_type n) const noexcept {
        return iota_iterator(current_ - (step_ * static_cast<T>(n)), step_);
    }

    constexpr difference_type operator-(
        const iota_iterator& other) const noexcept {
        return static_cast<difference_type>((current_ - other.current_) /
                                            step_);
    }

    constexpr T operator[](difference_type n) const noexcept {
        return current_ + (step_ * static_cast<T>(n));
    }

    constexpr auto operator<=>(const iota_iterator& other) const noexcept {
        return step_ > 0 ? (current_ <=> other.current_)
                         : (other.current_ <=> current_);
    }

    constexpr bool operator==(const iota_iterator& other) const noexcept {
        return current_ == other.current_;
    }
};

template <typename T>
class iota_view {
    T start_, end_, step_;

public:
    using iterator = iota_iterator<T>;
    using const_iterator = iterator;
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    constexpr iota_view(T start, T end, T step = T{1}) noexcept
        : start_(start), end_(end), step_(step) {
        if (step_ < 0 && start_ > end_) {
            auto diff = start_ - end_;
            auto steps = diff / (-step_);
            if (diff % (-step_) != 0) {
                steps++;
            }
            end_ = start_ - (steps * (-step_));
        } else if (step_ > 0 && start_ > end_) {
            start_ = end_;
        }
    }

    constexpr iterator begin() const noexcept {
        return iterator(start_, step_);
    }

    constexpr iterator end() const noexcept { return iterator(end_, step_); }

    constexpr bool empty() const noexcept {
        return (step_ > 0) ? (start_ >= end_) : (start_ <= end_);
    }

    constexpr size_type size() const noexcept {
        if (empty()) {
            return 0;
        }
        if (step_ > 0) {
            return static_cast<size_type>((end_ - start_ + step_ - 1) / step_);
        }
        return static_cast<size_type>((start_ - end_ + (-step_) - 1) /
                                      (-step_));
    }
};

struct Range {
    template <typename Sentinel>
    constexpr auto operator()(Sentinel sentinel) const noexcept {
        using T = std::common_type_t<int, Sentinel>;
        return iota_view<T>(T{0}, static_cast<T>(sentinel));
    }

    template <typename Start, typename Sentinel>
    constexpr auto operator()(Start start, Sentinel sentinel) const noexcept {
        using T = std::common_type_t<Start, Sentinel>;
        return iota_view<T>(static_cast<T>(start), static_cast<T>(sentinel));
    }

    template <typename Start, typename Sentinel, typename Step>
    constexpr auto operator()(Start start, Sentinel sentinel,
                              Step step) const noexcept {
        using T = std::common_type_t<Start, Sentinel, Step>;
        return iota_view<T>(static_cast<T>(start), static_cast<T>(sentinel),
                            static_cast<T>(step));
    }
};
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
constexpr Range iota{};
#pragma GCC diagnostic pop
}  // namespace

struct Point {
    int x = 0, y = 0, z = 0;
};

#include <cstdint>
#include <vector>

class UnionFind {
    std::vector<size_t> data;
    std::vector<uint8_t> rank;
    std::vector<size_t> cluster;

public:
    void init(size_t n) {
        data.resize(n);
        rank.assign(n, 0);
        cluster.assign(n, 1);
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
    auto find(auto x) { return x != data[x] ? find(data[x]) : x; }
    void merge(size_t x, size_t y) {
        x = find(x), y = find(y);
        if (x == y) {
            return;
        }
        if (rank[x] < rank[y]) {
            data[x] = y;
            cluster[y] += cluster[x];
        } else if (rank[x] > rank[y]) {
            data[y] = x;
            cluster[x] += cluster[y];
        } else {
            data[y] = x;
            cluster[x] += cluster[y];
            rank[x]++;
        }
    }
    auto size(auto x) { return cluster[find(x)]; }
};

#include <algorithm>

class Solver {
    std::vector<Point> ptrs;
    std::vector<std::vector<int64_t>> dists;
    struct Dist_Info {
        int64_t dist;
        size_t x, y;
    };
    std::vector<Dist_Info> dist_infos;
    UnionFind uf;
    int64_t dist(Point const& lhs, Point const& rhs) {
        auto x_diff = as<int64_t>(lhs.x) - rhs.x;
        auto y_diff = as<int64_t>(lhs.y) - rhs.y;
        auto z_diff = as<int64_t>(lhs.z) - rhs.z;
        return (x_diff * x_diff) + (y_diff * y_diff) + (z_diff * z_diff);
    }

    void read() {
        int x, y, z;
        char temp;
        while (cin >> x >> temp >> y >> temp >> z) {
            Point ptr{.x = x, .y = y, .z = z};
            ptrs.push_back(ptr);
        }
    }
    void set_dist() {
        auto n = ptrs.size();
        dists.resize(n, std::vector(n, 0L));
        for (auto i : iota(n)) {
            for (auto j : iota(i + 1, n)) {
                dists[i][j] = dists[j][i] = dist(ptrs[i], ptrs[j]);
                dist_infos.emplace_back(dist(ptrs[i], ptrs[j]), i, j);
            }
        }
        std::ranges::sort(dist_infos, [](auto lhs, auto rhs) {
            return std::tie(lhs.dist, lhs.x, lhs.y) <
                   std::tie(rhs.dist, rhs.x, rhs.y);
        });
    }
    int32_t part_1() {
        int32_t cnt = 0;
        uf.init(ptrs.size());
        for (auto [_, i, j] : dist_infos) {
            uf.merge(i, j);
            cnt += 1;
            if (cnt == 1000) {
                break;
            }
        }
        std::vector<int32_t> maxes;
        for (auto i : iota(ptrs.size())) {
            if (uf.find(i) == i) {
                maxes.push_back(uf.size(i));
            }
        }
        std::ranges::sort(maxes, std::greater<>{});
        return maxes[0] * maxes[1] * maxes[2];
    }
    int32_t part_2() {
        uf.init(ptrs.size());
        for (auto [_, i, j] : dist_infos) {
            uf.merge(i, j);
            if (uf.size(i) == ptrs.size()) {
                return ptrs[i].x * ptrs[j].x;
            }
        }
        std::unreachable();
    }

public:
    void solve() {
        read();
        set_dist();
        cout << part_1() << '\n';
        cout << part_2();
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
