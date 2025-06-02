/*==== Copyright 2025 Azruine ====*/

#include <algorithm>
#include <complex>
#include <iostream>
#include <numbers>
#include <utility>
#include <vector>

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
}  // namespace

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

class Solver {
public:
    void solve() {
        char chr{0};
        while (cin.get(chr) && chr >= '0' && chr <= '9') {
            input_1.push_back(chr - '0');
        }
        while (cin.get(chr) && chr >= '0' && chr <= '9') {
            input_2.push_back(chr - '0');
        }
        result = fft::multiply(input_1, input_2);
        std::ranges::reverse(result);
        int32_t cur_carry{0};
        for (size_t i{0}; i < result.size(); ++i) {
            result[i] += cur_carry;
            cur_carry = result[i] / TEN;
            result[i] %= TEN;
        }
        while (cur_carry > 0) {
            result.push_back(cur_carry % TEN);
            cur_carry /= TEN;
        }
        while (result.size() > 1 && result.back() == 0) {
            result.pop_back();
        }
        std::ranges::reverse(result);
        for (size_t i{0}; i < result.size(); ++i) {
            cout << result[i];
        }
    }

private:
    constexpr static int32_t TEN{10};
    std::vector<int32_t> input_1;
    std::vector<int32_t> input_2;
    std::vector<int32_t> result;
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
