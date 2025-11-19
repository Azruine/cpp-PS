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

#include <cmath>
#include <print>
#include <queue>
#include <vector>

struct Point {
    int32_t x = 0, y = 0;
    double energy = 0.0;
    static bool is_in_range(Point const& lhs, Point const& rhs, int32_t range) {
        return ((lhs.x - rhs.x) * (lhs.x - rhs.x) +
                    (lhs.y - rhs.y) * (lhs.y - rhs.y) <=
                range * range);
    }
    void transfer(Point& other, int32_t level) {
        other.energy += energy / std::pow(2, level);
        energy = 0;
    }
};

class Solver {
    size_t n = 0;
    double default_energy = 0;
    int32_t temp_x = 0, temp_y = 0;
    int32_t range = 0;
    std::vector<Point> towers;
    std::vector<std::vector<size_t>> connected;
    std::vector<size_t> parents;
    void read() {
        cin >> n >> range >> default_energy >> temp_x >> temp_y;
        towers.resize(n + 1);
        connected.resize(n + 1);
        parents.assign(n + 1, 0);
        towers[0].x = temp_x, towers[0].y = temp_y;
        for (auto i : iota(1, n + 1)) {
            auto& tower = towers[i];
            cin >> temp_x >> temp_y;
            tower.x = temp_x, tower.y = temp_y, tower.energy = default_energy;
        }
    }
    void make_graph() {
        for (auto i : iota(n + 1)) {
            std::vector<size_t> neighbor;
            for (auto j : iota(n + 1)) {
                if (i == j) {
                    continue;
                }
                if (Point::is_in_range(towers[i], towers[j], range)) {
                    neighbor.emplace_back(j);
                }
            }
            connected[i] = std::move(neighbor);
        }
    }
    void bfs() {
        auto& root = towers[0];
        std::queue<std::pair<size_t, int32_t>> que;
        que.emplace(0, 0);
        std::vector<bool> visited(n + 1, false);
        visited[0] = true;
        while (!que.empty()) {
            auto [cur, depth] = que.front();
            que.pop();
            visited[cur] = true;
            for (auto const& next : connected[cur]) {
                if (visited[next]) {
                    continue;
                }
                parents[next] = cur;
                que.emplace(next, depth + 1);
                towers[next].transfer(root, depth);
            }
        }
    }
    double get_val() { return towers[0].energy; }

public:
    void solve() {
        read();
        make_graph();
        bfs();
        std::print("{:.2f}", get_val());
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
