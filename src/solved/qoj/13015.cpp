/*==== Copyright 2025 Azruine ====*/

#include <iostream>
#include <utility>

using std::cin, std::cout;

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

#include <complex>
#include <numbers>
#include <vector>

namespace fft {
using complex = std::complex<double>;
using std::conj;
template <typename T>
    requires std::is_integral_v<T>
class FFT {
    size_t cache_size = 0;
    std::vector<complex> roots;
    constexpr static double PI = std::numbers::pi_v<double>;

    void fill_roots(size_t n) {
        if (n <= cache_size) {
            return;
        }
        cache_size = n;
        roots.resize(n >> 1);
        for (size_t i = 0; i < (n >> 1); i++) {
            double ang = 2.0 * PI * i / n;
            roots[i] = complex(std::cos(ang), std::sin(ang));
        }
    }

    void fft(std::vector<complex>& data, bool invert = false) {
        size_t n = data.size();
        if (n == 1) {
            return;
        }

        fill_roots(n);

        for (size_t i = 1, j = 0; i < n; i++) {
            size_t bit = n >> 1;
            for (; j & bit; bit >>= 1) {
                j ^= bit;
            }
            j ^= bit;
            if (i < j) {
                std::swap(data[i], data[j]);
            }
        }

        for (size_t k = 1; k < n; k <<= 1) {
            size_t step = cache_size / (k * 2);
            for (size_t i = 0; i < n; i += k * 2) {
                size_t idx = 0;
                for (size_t j = 0; j < k; j++) {
                    complex w = roots[idx];
                    if (invert) {
                        w = conj(w);
                    }
                    complex even = data[i + j];
                    complex odd = data[i + j + k] * w;
                    data[i + j] = even + odd;
                    data[i + j + k] = even - odd;
                    idx += step;
                }
            }
        }

        if (invert) {
            for (size_t i = 0; i < n; i++) {
                data[i] /= static_cast<double>(n);
            }
        }
    }

public:
    std::vector<T> multiply(std::vector<T> const& lhs,
                            std::vector<T> const& rhs) {
        if (lhs.empty() || rhs.empty()) {
            return {};
        }
        constexpr size_t NAIVE_THRESHOLD = 64;
        if (lhs.size() * rhs.size() <= NAIVE_THRESHOLD * NAIVE_THRESHOLD) {
            std::vector<T> ret(lhs.size() + rhs.size() - 1, 0);
            for (size_t i = 0; i < lhs.size(); i++) {
                if (lhs[i] == 0) {
                    continue;
                }
                for (size_t j = 0; j < rhs.size(); j++) {
                    ret[i + j] += lhs[i] * rhs[j];
                }
            }
            return ret;
        }

        size_t result_size = lhs.size() + rhs.size() - 1;
        size_t n = 2;
        while (n < result_size) {
            n <<= 1;
        }

        std::vector<complex> pack(n);
        for (size_t i = 0; i < lhs.size(); i++) {
            pack[i].real(static_cast<double>(lhs[i]));
        }
        for (size_t i = 0; i < rhs.size(); i++) {
            pack[i].imag(static_cast<double>(rhs[i]));
        }

        std::vector<T> ret(result_size);

        fft(pack);
        for (size_t i = 0; i < n; i++) {
            pack[i] *= pack[i];
        }
        fft(pack, true);
        for (size_t i = 0; i < result_size; i++) {
            ret[i] = static_cast<T>(std::lround(pack[i].imag() * 0.5));
        }

        return ret;
    }
    std::vector<T> self_multiply(std::vector<T> const& vec) {
        if (vec.empty()) {
            return {};
        }
        size_t result_size = (2 * vec.size()) - 1;
        size_t n = 2;
        while (n < result_size) {
            n <<= 1;
        }
        std::vector<complex> fft_data(n);
        for (size_t i = 0; i < vec.size(); i++) {
            fft_data[i] = complex(static_cast<double>(vec[i]), 0.0);
        }
        fft(fft_data);
        for (size_t i = 0; i < n; i++) {
            fft_data[i] *= fft_data[i];
        }
        fft(fft_data, true);
        std::vector<T> result(result_size);
        for (size_t i = 0; i < result_size; i++) {
            result[i] = static_cast<T>(std::lround(fft_data[i].real()));
        }
        return result;
    }
};
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
                if (prime > min_factor[i] || prime > n / i) {
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

#include <algorithm>
#include <print>
#include <ranges>

class Solver {
    constexpr static int32_t MAX = 100;
    constexpr static int32_t MAX_DIGIT = 2;
    fft::FFT<int32_t> fft;
    int64_t pow(int64_t base, int64_t pow) {
        int64_t ret = 1;
        while (pow) {
            if (pow & 1) {
                ret *= base;
            }
            pow >>= 1;
            base *= base;
        }
        return ret;
    }
    std::vector<int32_t> product(std::vector<std::vector<int32_t>>& tree) {
        if (tree.empty()) {
            return {1};
        }
        if (tree.size() == 1) {
            return std::move(tree[0]);
        }
        return {0};
    }
    void normalize(std::vector<int32_t>& number) {
        if (number.empty()) {
            return;
        }
        while (number.back() == 0) {
            number.pop_back();
        }
        size_t n = number.size();
        int32_t carry = 0;
        for (size_t i = 0; i < n; i++) {
            int32_t value = carry + number[i];
            carry = value / MAX;
            number[i] = value % MAX;
        }
        while (carry > 0) {
            number.emplace_back(carry % MAX);
            carry /= MAX;
        }
    }
    void subtract(std::vector<int32_t>& number) {
        if (number.empty()) {
            exit(-1);
        }
        size_t n = number.size();
        int32_t carry = -1;
        for (size_t i = 0; i < n; i++) {
            int32_t value = carry + number[i];
            carry = 0;
            while (value < 0) {
                carry -= 1;
                value += MAX;
            }
            number[i] = value % MAX;
            carry += value / MAX;
        }
        if (carry < 0) {
            exit(-1);
        }
    }

public:
    void solve() {
        int32_t n = 0;
        cin >> n;
        if (n == 1) {
            cout << "! 1";
            return;
        }
        sieve::LinearSieve<int32_t> sieve{n};
        auto& primes = sieve.get_primes();
        std::vector<std::vector<int32_t>> products;
        for (auto prime : primes) {
            auto upper_exp = std::lround(std::log(n) / std::log(prime)) + 1;
            auto factor = pow(prime, upper_exp);
            while (factor > n) {
                factor /= prime;
            }
            std::vector<int32_t> value;
            while (factor > 0) {
                value.emplace_back(factor % MAX);
                factor /= MAX;
            }
            products.emplace_back(std::move(value));
        }
        auto cmp = [](auto&& lhs, auto&& rhs) {
            return lhs.size() > rhs.size();
        };
        auto pop_min = [&]() {
            std::ranges::pop_heap(products, cmp);
            auto value = std::move(products.back());
            products.pop_back();
            return value;
        };
        std::ranges::make_heap(products, cmp);
        while (products.size() > 1) {
            auto lhs = pop_min();
            auto rhs = pop_min();
            auto result = fft.multiply(lhs, rhs);
            normalize(result);
            products.emplace_back(std::move(result));
            std::ranges::push_heap(products, cmp);
        }
        subtract(products.back());
        std::string print;
        print = "? ";
        for (auto const& value : products[0] | std::views::reverse) {
            print += std::format(":0{}d", value, MAX_DIGIT);
        }
        std::print("{}\n", print);
        std::fflush(stdout);
        cin >> n;
        std::print("! {}\n", n + 1);
    }
};

int main() {
    Solver solver;
    solver.solve();
    return 0;
}
