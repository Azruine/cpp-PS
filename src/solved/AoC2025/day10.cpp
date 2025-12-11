/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <iostream>
#include <limits>
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

#include <bitset>
#include <numeric>
#include <queue>
#include <string>
#include <vector>

class Solver {
    constexpr static int32_t TEN = 10;
    constexpr static size_t MAX = 1 << TEN;
    using bit = std::bitset<TEN>;
    struct GaussResult {
        std::vector<int64_t> denom;
        std::vector<std::vector<int64_t>> num;
        std::vector<std::optional<size_t>> pivot_col;
        size_t rank = 0;
    };
    size_t n = 0;
    std::vector<bit> targets;
    std::vector<std::vector<int32_t>> electricites;
    std::vector<std::vector<bit>> switches;
    void read() {
        std::string temp;
        while (cin >> temp) {
            auto len = temp.length();
            if (temp[0] == '[') {
                // start new machine
                n++;
                electricites.emplace_back();
                switches.emplace_back();
                bit cur_target;
                for (auto i = 1UL; i < len - 1; i++) {
                    if (temp[i] == '#') {
                        cur_target.flip(i - 1);
                    }
                }
                targets.emplace_back(cur_target);
            }
            if (temp[0] == '(') {
                // start new switch
                bit cur_switch;
                for (auto i = 1UL; i < len - 1; i += 2) {
                    auto num = as<size_t>(temp[i] - '0');
                    cur_switch.flip(num);
                }
                switches[n - 1].emplace_back(cur_switch);
            }
            if (temp[0] == '{') {
                // electricity, not used in pt1 but parse anyway
                size_t i = 1;
                while (i < len - 1) {
                    int32_t val = 0;
                    while (std::isdigit(temp[i])) {
                        val = val * TEN + (temp[i] - '0');
                        i++;
                    }
                    // go one more
                    i++;
                    electricites[n - 1].push_back(val);
                }
            }
        }
    }
    uint32_t part_1() {
        uint32_t ret = 0;
        for (auto i : iota(n)) {
            std::vector<std::optional<uint32_t>> dist(MAX);
            std::queue<uint32_t> que;
            que.push(0);
            dist[0] = 0;
            auto target = as<uint32_t>(targets[i].to_ulong());
            while (!que.empty()) {
                auto cur = que.front();
                que.pop();
                if (cur == target) {
                    ret += dist[cur].value();
                    break;
                }
                for (auto const& sw : switches[i]) {
                    auto next = cur ^ as<uint32_t>(sw.to_ulong());
                    if (!dist[next].has_value()) {
                        dist[next] = dist[cur].value() + 1;
                        que.push(next);
                    }
                }
            }
        }
        return ret;
    }
    int64_t part_2() {
        int64_t ret = 0;
        for (auto idx : iota(n)) {
            auto gauss_res = gauss_eliminate(idx);
            auto free_vars = find_free_vars(gauss_res, switches[idx].size());
            ret +=
                search_minimum(gauss_res, free_vars, switches[idx].size(), idx);
        }
        return ret;
    }
    GaussResult gauss_eliminate(size_t idx) {
        auto& target = electricites[idx];
        auto& btns = switches[idx];
        size_t row_mat = target.size();
        size_t col_mat = btns.size();
        std::vector<std::vector<int64_t>> mat(
            row_mat, std::vector<int64_t>(col_mat + 1));
        for (auto i : iota(row_mat)) {
            for (auto j : iota(col_mat)) {
                mat[i][j] = btns[j][i] ? 1 : 0;
            }
            mat[i][col_mat] = target[i];
        }

        std::vector<std::optional<size_t>> pivot_col(row_mat);
        size_t pivot_cnt = 0;
        for (size_t cur_col = 0; cur_col < col_mat && pivot_cnt < row_mat;
             cur_col++) {
            std::optional<size_t> pivot;
            for (auto row : iota(pivot_cnt, row_mat)) {
                if (mat[row][cur_col] != 0) {
                    pivot = row;
                    break;
                }
            }
            if (!pivot.has_value()) {
                continue;
            }
            std::swap(mat[pivot_cnt], mat[pivot.value()]);
            pivot_col[pivot_cnt] = cur_col;
            for (auto row : iota(row_mat)) {
                if (row != pivot_cnt && mat[row][cur_col] != 0) {
                    int64_t a = mat[pivot_cnt][cur_col];
                    int64_t b = mat[row][cur_col];
                    for (auto col : iota(col_mat + 1)) {
                        mat[row][col] =
                            mat[row][col] * a - mat[pivot_cnt][col] * b;
                    }
                    int64_t gcd = 0;
                    for (auto col : iota(col_mat + 1)) {
                        gcd = std::gcd(gcd, std::abs(mat[row][col]));
                    }
                    if (gcd > 1) {
                        for (auto col : iota(col_mat + 1)) {
                            mat[row][col] /= gcd;
                        }
                    }
                }
            }
            pivot_cnt++;
        }

        GaussResult result;
        result.pivot_col = std::move(pivot_col);
        result.rank = pivot_cnt;
        for (auto row : iota(pivot_cnt)) {
            auto pivot_col_idx = result.pivot_col[row].value();
            result.denom.push_back(mat[row][pivot_col_idx]);
            result.num.push_back(std::move(mat[row]));
        }
        return result;
    }
    std::vector<size_t> find_free_vars(GaussResult const& gauss_res,
                                       size_t num_vars) {
        std::vector<size_t> free_vars;
        size_t pivot_idx = 0;
        for (auto col : iota(num_vars)) {
            if (pivot_idx < gauss_res.rank &&
                gauss_res.pivot_col[pivot_idx].has_value() &&
                gauss_res.pivot_col[pivot_idx].value() == col) {
                pivot_idx++;
            } else {
                free_vars.push_back(col);
            }
        }
        return free_vars;
    }
    int64_t search_minimum(GaussResult const& gauss_res,
                           std::vector<size_t> const& free_vars,
                           size_t num_vars, size_t idx) {
        auto ret = std::numeric_limits<int64_t>::max();
        auto upper = *std::ranges::max_element(electricites[idx]);
        std::vector<int64_t> free_vals(free_vars.size());
        std::vector<int64_t> sol(num_vars);
        auto search = [&](this auto&& self, size_t free_idx) -> void {
            if (free_idx == free_vars.size()) {
                std::ranges::fill(sol, 0);
                for (size_t j = 0; j < free_vars.size(); j++) {
                    sol[free_vars[j]] = free_vals[j];
                }
                for (auto row = gauss_res.rank - 1; row < gauss_res.rank;
                     row--) {
                    auto pivot = gauss_res.pivot_col[row].value();
                    int64_t num = gauss_res.num[row][num_vars];
                    for (auto col = pivot + 1; col < num_vars; col++) {
                        num -= gauss_res.num[row][col] * sol[col];
                    }
                    if (num % gauss_res.denom[row] != 0) {
                        return;
                    }
                    int64_t val = num / gauss_res.denom[row];
                    if (val < 0) {
                        return;
                    }
                    sol[pivot] = val;
                }
                auto sum = std::ranges::fold_left(sol, 0L, std::plus<>{});
                ret = std::min(ret, sum);
                return;
            }
            for (int32_t val = 0; val <= upper; val++) {
                free_vals[free_idx] = val;
                self(free_idx + 1);
            }
        };
        search(0);
        return ret;
    }

public:
    void solve() {
        read();
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
