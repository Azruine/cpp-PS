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

#include <queue>
#include <vector>

struct Node {
    size_t id = 0;
    std::vector<std::pair<size_t, int>> edges;
};

class Graph {
    using P = std::pair<int, size_t>;
    using EDGE = std::pair<size_t, int>;
    std::vector<Node> m_nodes;
    std::vector<int> m_distances;

public:
    void init(size_t n) {
        m_nodes.clear();
        m_distances.clear();
        m_nodes.resize(n);
        m_distances.resize(n, INT32_MAX);
        for (auto i : iota(0, n)) {
            m_nodes[i].id = i;
        }
    }
    void add_edge(size_t start, size_t end, int weight) {
        m_nodes[start].edges.emplace_back(end, weight);
    }
    void dijkstra(size_t start) {
        m_distances[start] = 0;
        std::vector<bool> visited(m_nodes.size(), false);
        std::priority_queue<P, std::vector<P>, std::greater<>> pq;
        pq.emplace(0, start);
        while (!pq.empty()) {
            auto [cur_dist, cur_id] = pq.top();
            pq.pop();
            if (visited[cur_id]) {
                continue;
            }
            visited[cur_id] = true;
            for (auto [next_id, weight] : m_nodes[cur_id].edges) {
                if (m_distances[next_id] > cur_dist + weight) {
                    m_distances[next_id] = cur_dist + weight;
                    pq.emplace(m_distances[next_id], next_id);
                }
            }
        }
    }
    [[nodiscard("Distance value not used.")]] int32_t get_distance(
        size_t node) const {
        return m_distances[node];
    }
    [[nodiscard("Edge vector not used.")]] std::vector<EDGE> const& get_edges(
        size_t node) const {
        return m_nodes[node].edges;
    }
};

class Solver {
    size_t m_n = 0, m_m = 0;
    size_t m_start = 0, m_dest = 0;
    Graph graph, rev_graph, deleted_graph;

    bool read() {
        cin >> m_n >> m_m;
        if (m_n == 0 && m_m == 0) {
            return false;
        }
        cin >> m_start >> m_dest;
        graph.init(m_n);
        rev_graph.init(m_n);
        for (auto _ : iota(0, m_m)) {
            size_t start = 0;
            size_t end = 0;
            int weight = 0;
            cin >> start >> end >> weight;
            graph.add_edge(start, end, weight);
            rev_graph.add_edge(end, start, weight);
        }
        return true;
    }

    void find_deleted_edges() {
        graph.dijkstra(m_start);
        rev_graph.dijkstra(m_dest);
        int shortest_path_length = graph.get_distance(m_dest);
        deleted_graph.init(m_n);
        for (auto start : iota(0, m_n)) {
            for (auto [end, weight] : graph.get_edges(start)) {
                // clang-format off
                if (graph.get_distance(start) + weight + rev_graph.get_distance(end) != shortest_path_length
                    || graph.get_distance(start) == INT32_MAX
                    || rev_graph.get_distance(end) == INT32_MAX) {
                    deleted_graph.add_edge(start, end, weight);
                }
                // clang-format on
            }
        }
        deleted_graph.dijkstra(m_start);
    }
    void print() {
        int result = deleted_graph.get_distance(m_dest);
        if (result == INT32_MAX) {
            result = -1;
        }
        cout << result << '\n';
    }

public:
    void solve() {
        while (read()) {
            find_deleted_edges();
            print();
        }
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
