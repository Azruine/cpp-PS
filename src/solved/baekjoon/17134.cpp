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

#include <complex>
#include <numbers>
#include <vector>

namespace fft {
using complex = std::complex<double>;
void fft(std::vector<complex>& data, bool invert = false) {
    constexpr static double PI_ = std::numbers::pi_v<double>;
    size_t n{data.size()};
    if (n == 1) {
        return;
    }
    for (size_t i{0}, j{0}; i < n; i++) {
        if (i < j) {
            std::swap(data[i], data[j]);
        }
        size_t bit = n >> 1;
        while (j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;
    }
    for (size_t k{1}; k < n; k <<= 1) {
        double angle{invert ? PI_ / static_cast<double>(k)
                            : -PI_ / static_cast<double>(k)};
        complex roots{std::cos(angle), std::sin(angle)};
        for (size_t i{0}; i < n; i += k * 2) {
            complex z{1, 0};
            for (size_t j{0}; j < k; j++) {
                complex even{data[i + j]};
                complex odd{data[i + j + k] * z};
                data[i + j] = even + odd;
                data[i + j + k] = even - odd;
                z *= roots;
            }
        }
    }
    if (invert) {
        for (size_t i{0}; i < n; i++) {
            data[i] /= static_cast<double>(n);
        }
    }
}

template <typename T>
    requires std::is_integral_v<T>
std::vector<T> multiply(std::vector<T> const& lhs, std::vector<T> const& rhs) {
    size_t result_size = lhs.size() + rhs.size() - 1;
    size_t n = 2;
    while (n < result_size) {
        n <<= 1;
    }
    std::vector<complex> fft_data(n);
    std::vector<T> result(result_size);
    for (size_t i = 0; i < lhs.size(); ++i) {
        fft_data[i] = complex(static_cast<double>(lhs[i]), 0.0);
    }
    std::fill(fft_data.begin() + as<int64_t>(lhs.size()), fft_data.end(),
              complex(0, 0));
    fft(fft_data);
    std::vector<complex> lhs_fft = std::move(fft_data);
    fft_data.assign(n, complex(0, 0));
    for (size_t i = 0; i < rhs.size(); ++i) {
        fft_data[i] = complex(static_cast<double>(rhs[i]), 0.0);
    }
    fft(fft_data);
    for (size_t i = 0; i < n; ++i) {
        fft_data[i] *= lhs_fft[i];
    }
    fft(fft_data, true);
    for (size_t i = 0; i < result_size; ++i) {
        result[i] = static_cast<T>(std::lround(fft_data[i].real()));
    }
    return result;
}

template <typename T>
    requires std::is_integral_v<T>
std::vector<T> self_multiply(std::vector<T> const& vec) {
    size_t result_size = (2 * vec.size()) - 1;
    size_t n = 2;
    while (n < result_size) {
        n <<= 1;
    }
    std::vector<complex> fft_data(n);
    for (size_t i = 0; i < vec.size(); ++i) {
        fft_data[i] = complex(static_cast<double>(vec[i]), 0.0);
    }
    fft(fft_data);
    for (size_t i = 0; i < n; ++i) {
        fft_data[i] *= fft_data[i];
    }
    fft(fft_data, true);
    std::vector<T> result(result_size);
    for (size_t i = 0; i < result_size; ++i) {
        result[i] = static_cast<T>(std::lround(fft_data[i].real()));
    }
    return result;
}
};  // namespace fft

namespace sieve {
template <typename T>
    requires std::is_integral_v<T>
class LinearSieve {
public:
    explicit LinearSieve(T n) : is_prime(n + 1, true), min_factor(n + 1, 0) {
        is_prime[0] = is_prime[1] = false;
        for (T i = 2; i <= n; ++i) {
            if (is_prime[i]) {
                primes.push_back(i);
                min_factor[i] = i;
            }
            for (const T& prime : primes) {
                if (prime * i > n || prime > min_factor[i]) {
                    break;
                }
                is_prime[prime * i] = false;
                min_factor[prime * i] = prime;
            }
        }
    }
    std::vector<T> const& get_primes() const { return primes; }
    std::vector<bool> const& get_is_prime() const { return is_prime; }
    std::vector<T> const& get_min_factor() const { return min_factor; }

private:
    std::vector<T> primes;
    std::vector<bool> is_prime;
    std::vector<T> min_factor;
};
};  // namespace sieve

class Solver {
    size_t t = 0, n = 0;
    constexpr static size_t MAX_N = 1'000'010;
    std::vector<size_t> m_semiprime;
    std::vector<size_t> m_data;
    std::vector<size_t> m_prime;
    std::vector<size_t> m_is_prime;
    void init() {
        m_is_prime.resize(MAX_N, 1);
        m_is_prime[0] = m_is_prime[1] = 0;
        for (size_t i : iota(2, MAX_N)) {
            if (m_is_prime[i]) {
                m_prime.push_back(i);
            }
            for (auto const& prime : m_prime) {
                if (as<size_t>(prime) * i >= MAX_N) {
                    break;
                }
                m_is_prime[as<size_t>(prime) * i] = 0;
                if (i % as<size_t>(prime) == 0) {
                    break;
                }
            }
        }
        m_is_prime[2] = 0;

        m_semiprime.resize(MAX_N, 0);
        for (auto const& prime : m_prime) {
            if (prime * 2 >= MAX_N) {
                break;
            }
            m_semiprime[prime * 2] = 1;
        }

        m_data = fft::multiply(m_is_prime, m_semiprime);
    }

public:
    void solve() {
        cin >> t;
        init();
        while (cin >> n) {
            cout << m_data[n] << '\n';
        }
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
