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
#include <map>
#include <sstream>
#include <string>
#include <vector>

class Solver {
    std::vector<std::vector<size_t>> graph;
    std::map<std::string, size_t> string_to_node;
    size_t node_idx(std::string const& str) {
        size_t ret = 0;
        if (!string_to_node.contains(str)) {
            ret = string_to_node.size();
            string_to_node[str] = ret;
            graph.emplace_back();
        } else {
            ret = string_to_node[str];
        }
        return ret;
    }
    void read() {
        std::string line;
        while (std::getline(cin, line)) {
            std::stringstream sstr(line);
            std::string temp;
            sstr >> temp;
            // remove ':'
            temp.pop_back();
            size_t start_node = node_idx(temp);
            while (sstr >> temp) {
                size_t end_node = node_idx(temp);
                graph[start_node].push_back(end_node);
            }
        }
    }
    int32_t part_1() {
        size_t start = node_idx("you");
        size_t end = node_idx("out");
        std::vector<std::optional<int32_t>> dp(graph.size());
        auto& graph_lambda = graph;
        auto dfs = [&](this auto&& self, size_t idx) {
            if (idx == end) {
                return 1;
            }
            if (dp[idx].has_value()) {
                return dp[idx].value();
            }
            int32_t cnt = 0;
            for (auto const& next : graph_lambda[idx]) {
                cnt += self(next);
            }
            dp[idx] = cnt;
            return dp[idx].value();
        };
        return dfs(start);
    }
    std::vector<size_t> topological_sort() {
        std::vector<size_t> ret;
        std::vector<bool> visited(graph.size(), false);
        auto& graph_lambda = graph;
        auto dfs = [&](this auto&& self, size_t node) -> void {
            visited[node] = true;
            for (auto const& next : graph_lambda[node]) {
                if (!visited[next]) {
                    self(next);
                }
            }
            ret.push_back(node);
        };
        for (auto i : iota(graph.size())) {
            if (!visited[i]) {
                dfs(i);
            }
        }
        std::ranges::reverse(ret);
        return ret;
    }
    int64_t part_2() {
        size_t start = node_idx("svr");
        size_t end = node_idx("out");
        size_t fft = node_idx("fft");
        size_t dac = node_idx("dac");
        // 0 -> fft, 1 -> dac
        constexpr static int32_t FFT = 0;
        constexpr static int32_t DAC = 1;
        constexpr static int32_t REQ = 2;
        std::vector<std::vector<std::optional<int64_t>>> dp(
            graph.size(), std::vector<std::optional<int64_t>>(1 << REQ));
        dp[start][0] = 1;  // start node will not be fft or dac
        auto topo = topological_sort();
        for (auto const& node : topo) {
            for (auto const& next : graph[node]) {
                for (auto mask : iota(1U << REQ)) {
                    if (!dp[node][mask].has_value()) {
                        continue;
                    }
                    auto new_mask = mask;
                    if (next == fft) {
                        new_mask |= (1 << FFT);
                    }
                    if (next == dac) {
                        new_mask |= (1 << DAC);
                    }
                    if (!dp[next][new_mask].has_value()) {
                        dp[next][new_mask] = 0;
                    }
                    dp[next][new_mask].value() += dp[node][mask].value();
                }
            }
        }
        return dp[end][(1 << 2) - 1].value();
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
