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

#include <vector>

class Solver {
    size_t m_n = 0;
    size_t m_even = 0;
    size_t m_odd = 0;
    // 0: not placable, 1: placable
    std::vector<std::vector<int>> m_board;
    /*
    from top left to bottom right
    n - 1, 0 => 0
    n - 2, 0 / n - 1, 1 => 1
    n - 3, 0 / n - 2, 1 / n - 1, 2 = > 2

    n - 1 - (row - col) is idx

    to find all cells:
    n - 1 - idx, 0 ... n - 1, idx
    */
    std::vector<bool> m_dia_topleft;
    /*
    from top right to bottom left
    0, 0 => 0
    1, 0 / 0, 1 => 1

    row + col is idx

    to find all cells:
    idx, 0 ... 0, idx
    */
    std::vector<bool> m_dia_topright;
    void read() {
        cin >> m_n;
        m_board.resize(m_n, std::vector<int>(m_n, 0));
        m_dia_topleft.resize((2 * m_n) - 1);
        m_dia_topright.resize((2 * m_n) - 1);
        for (auto row : iota(m_n)) {
            for (auto col : iota(m_n)) {
                cin >> m_board[row][col];
            }
        }
    }
    void backtracking(size_t cnt, size_t cur_dia_topright) {
        // depth restriction
        if (cur_dia_topright >= 2 * m_n - 1) {
            (cur_dia_topright & 1) ? m_odd = std::max(m_odd, cnt)
                                   : m_even = std::max(m_even, cnt);
            return;
        }
        // iterate through all valid cells
        for (auto row : iota(cur_dia_topright + 1)) {
            auto col = cur_dia_topright - row;
            if (row >= m_n || col >= m_n) {
                continue;
            }
            auto cur_dia_topleft = m_n - 1 - (row - col);
            if (m_board[row][col] == 0 || m_dia_topleft[cur_dia_topleft] ||
                m_dia_topright[cur_dia_topright]) {
                continue;
            }
            // backtracking
            m_dia_topleft[cur_dia_topleft] = true;
            m_dia_topright[cur_dia_topright] = true;
            backtracking(cnt + 1, cur_dia_topright + 2);
            m_dia_topleft[cur_dia_topleft] = false;
            m_dia_topright[cur_dia_topright] = false;
        }
        backtracking(cnt, cur_dia_topright + 2);
    }

public:
    void solve() {
        read();
        backtracking(0, 0);
        backtracking(0, 1);
        cout << m_even + m_odd;
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
