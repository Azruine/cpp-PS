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
            end_ = start_ - steps * (-step_);
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

#include <algorithm>
#include <functional>
#include <limits>
#include <optional>
#include <queue>
#include <vector>

class Solver {
    constexpr static int32_t INF = std::numeric_limits<int32_t>::max() >> 1;
    size_t _n = 0, _m = 0;
    std::vector<std::vector<std::pair<size_t, int32_t>>> _graph;
    void read() {
        cin >> _n >> _m;
        _graph.resize(_n);
        size_t u = 0;
        size_t v = 0;
        int32_t w = 0;
        for (auto _ : iota(_m)) {
            cin >> u >> v >> w;
            u -= 1;
            v -= 1;
            _graph[u].emplace_back(v, w);
        }
    }
    std::tuple<int32_t, std::vector<size_t>> get_dist(size_t start,
                                                      size_t end) {
        std::vector<bool> visited(_n, false);
        std::vector<int32_t> dist(_n, INF);
        std::vector<std::optional<size_t>> parent(_n, std::nullopt);
        using Node = std::tuple<int32_t, size_t>;
        std::priority_queue<Node, std::vector<Node>, std::greater<>> pq;
        pq.emplace(0, start);
        dist[start] = 0;
        visited[start] = true;
        while (!pq.empty()) {
            auto [cur_weight, cur] = pq.top();
            pq.pop();
            if (dist[cur] != cur_weight) {
                continue;
            }
            if (cur == end) {
                break;
            }
            for (auto const& [next, weight] : _graph[cur]) {
                if (dist[next] > cur_weight + weight) {
                    dist[next] = cur_weight + weight;
                    parent[next] = cur;
                    pq.emplace(dist[next], next);
                }
            }
        }
        if (dist[end] == INF) {
            return {-1, {}};
        }
        std::vector<size_t> path;
        for (auto cur = end;;) {
            path.push_back(cur);
            if (!parent[cur].has_value()) {
                break;
            }
            cur = parent[cur].value();
        }
        std::ranges::reverse(path);
        return {dist[end], path};
    }

public:
    void solve() {
        read();
        size_t start, end;
        cin >> start >> end;
        start -= 1;
        end -= 1;
        auto [weight, path] = get_dist(start, end);
        cout << weight << '\n' << path.size() << '\n';
        for (auto const& node : path) {
            cout << node + 1 << ' ';
        }
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
