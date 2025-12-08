/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
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

#include <vector>

struct remove_char : std::ctype<char> {
    remove_char() : std::ctype<char>(get_table()) {}
    static mask const* get_table() {
        static std::vector<mask> masks(table_size, mask());
        std::copy(classic_table(), classic_table() + table_size, masks.begin());
        masks[','] = std::ctype_base::space;
        masks['-'] = std::ctype_base::space;
        return masks.data();
    }
};

std::ostream& operator<<(std::ostream& os, __int128_t n) {
    static constexpr int32_t TEN = 10;
    if (n == 0) {
        return os << "0";
    }
    if (n < 0) {
        os << '-';
        n = -n;
    }
    std::string str;
    while (n > 0) {
        str += as<char>('0' + (n % 10));
        n /= TEN;
    }
    for (size_t i = 0; i < str.length() / 2; i++) {
        std::swap(str[i], str[str.length() - 1 - i]);
    }
    return os << str;
}

class Solver {
    bool is_repeat(const std::string& s, size_t k) {
        size_t n = s.length();
        if (n % k != 0) {
            return false;
        }
        size_t pat = n / k;
        for (size_t i : iota(pat, n)) {
            if (s[i] != s[i - pat]) {
                return false;
            }
        }
        return true;
    }
    __int128_t part_1(int64_t left, int64_t right) {
        __int128_t ret = 0;
        for (auto i : iota(left, right + 1)) {
            auto str = std::to_string(i);
            if (is_repeat(str, 2)) {
                ret += i;
            }
        }
        return ret;
    }
    __int128_t part_2(int64_t left, int64_t right) {
        __int128_t ret = 0;
        for (auto i : iota(left, right + 1)) {
            auto str = std::to_string(i);
            bool found = false;
            for (size_t j : iota(2, str.length() + 1)) {
                if (str.length() % j != 0) {
                    continue;
                }
                if (is_repeat(str, j)) {
                    found = true;
                    break;
                }
            }
            if (found) {
                ret += i;
            }
        }
        return ret;
    }

public:
    void solve() {
        cin.imbue(std::locale(cin.getloc(), new remove_char));
        int64_t left, right;
        __int128_t p1 = 0, p2 = 0;
        while (cin >> left >> right) {
            p1 += part_1(left, right);
            p2 += part_2(left, right);
        }
        cout << p1 << '\n' << p2;
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
