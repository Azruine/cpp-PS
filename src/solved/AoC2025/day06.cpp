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

#include <algorithm>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

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
    std::vector<std::vector<int32_t>> grid;
    std::vector<char> op;
    std::string temp;
    void read_1() {
        while (std::getline(cin, temp)) {
            std::stringstream sstr(temp);
            if (temp[0] != ' ' && !std::isdigit(temp[0])) {
                char chr = 0;
                while (sstr >> chr) {
                    op.push_back(chr);
                }
                return;
            }
            int32_t var = 0;
            std::vector<int32_t> arr;
            while (sstr >> var) {
                arr.push_back(var);
            }
            grid.push_back(std::move(arr));
        }
    }
    __int128_t part_1() {
        size_t m = grid.size();
        size_t n = grid[0].size();
        __int128_t ret = 0;
        for (auto col : iota(n)) {
            char op_col = op[col];
            __int128_t res = op_col == '*' ? 1 : 0;
            for (auto row : iota(m)) {
                op_col == '*' ? res *= grid[row][col] : res += grid[row][col];
            }
            ret += res;
        }
        return ret;
    }
    void read_2() {
        grid.clear();
        std::vector<std::string> arr;
        size_t max = 0;
        while (std::getline(cin, temp)) {
            arr.push_back(std::move(temp));
            max = std::max(max, arr.back().size());
        }
        std::vector<int32_t> nums;
        for (auto col : iota(max)) {
            temp.clear();
            for (auto row : iota(arr.size())) {
                temp += arr[row][col];
            }
            if (std::ranges::all_of(
                    temp, [](char chr) { return std::isspace(chr); })) {
                // need to start new
                grid.push_back(std::move(nums));
                continue;
            }
            auto view =
                temp |
                std::views::filter([](char chr) { return std::isdigit(chr); }) |
                std::ranges::to<std::string>();
            nums.push_back(std::stoi(view));
        }
        if (!nums.empty()) {
            grid.push_back(std::move(nums));
        }
        for (auto chr : arr.back()) {
            if (!std::isspace(chr)) {
                op.push_back(chr);
            }
        }
    }
    __int128_t part_2() {
        __int128_t ret = 0;
        for (auto i : iota(grid.size())) {
            __int128_t res = op[i] == '*' ? 1 : 0;
            for (auto& num : grid[i]) {
                op[i] == '*' ? res *= num : res += num;
            }
            ret += res;
        }
        return ret;
    }

public:
    void solve() {
        // read_1();
        // cout << part_1();
        read_2();
        cout << part_2();
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
