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

#include <cassert>
#include <string>
#include <vector>

class Solver {
    size_t m_n = 0;
    std::vector<std::string> m_grid;
    void read() {
        cin >> m_n;
        m_grid.resize(m_n);
        for (auto& row : m_grid) {
            cin >> row;
        }
    }
    template <class Eq>
    void dfs(size_t row, size_t col, Eq equal,
             std::vector<std::string>& visited) {
        visited[row][col] = '1';
        static std::vector<std::pair<size_t, size_t>> stk;
        assert(stk.empty());
        stk.emplace_back(row, col);
        while (!stk.empty()) {
            auto [r, c] = stk.back();
            stk.pop_back();
            for (auto d_row : iota(-1, 2)) {
                for (auto d_col : iota(-1, 2)) {
                    if ((d_row + d_col) % 2 == 0) {
                        continue;
                    }
                    size_t nr = r + as<size_t>(d_row);
                    size_t nc = c + as<size_t>(d_col);
                    if (nr < m_n && nc < m_n && visited[nr][nc] == '0' &&
                        equal(m_grid[nr][nc], m_grid[r][c])) {
                        visited[nr][nc] = '1';
                        stk.emplace_back(nr, nc);
                    }
                }
            }
        }
    }
    template <class Eq>
    size_t get_free(Eq equal) {
        size_t area_cnt = 0;
        std::vector<std::string> visited(m_n, std::string(m_n, '0'));
        for (auto row : iota(m_n)) {
            for (auto col : iota(m_n)) {
                if (visited[row][col] == '0') {
                    area_cnt++;
                    dfs(row, col, equal, visited);
                }
            }
        }
        return area_cnt;
    }

public:
    void solve() {
        read();
        auto normal = [](char lhs, char rhs) { return lhs == rhs; };
        auto color_blind = [](char lhs, char rhs) {
            auto key = [](char chr) {
                return (chr == 'R' || chr == 'G') ? 'R' : chr;
            };
            return key(lhs) == key(rhs);
        };
        cout << get_free(normal) << ' ' << get_free(color_blind) << '\n';
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
