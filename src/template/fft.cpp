/*==== Copyright 2025 Azruine ====*/

#include <complex>
#include <numbers>
#include <vector>

namespace fft {
using complex = std::complex<double>;
void fft(std::vector<complex>& data, bool invert = false,
         bool precise = false) {
    constexpr static double PI_ = std::numbers::pi_v<double>;
    size_t n = data.size();
    if (n == 1) {
        return;
    }
    for (size_t i = 0, j = 0; i < n; i++) {
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
    if (precise) {
        for (size_t k = 1; k < n; k <<= 1) {
            double angle{invert ? PI_ / static_cast<double>(k)
                                : -PI_ / static_cast<double>(k)};

            for (size_t i = 0; i < n; i += k * 2) {
                for (size_t j = 0; j < k; j++) {
                    complex even = data[i + j];
                    complex w =
                        complex(std::cos(angle * j), std::sin(angle * j));
                    complex odd = data[i + j + k] * w;

                    data[i + j] = even + odd;
                    data[i + j + k] = even - odd;
                }
            }
        }
    } else {
        for (size_t k = 1; k < n; k <<= 1) {
            double angle{invert ? PI_ / static_cast<double>(k)
                                : -PI_ / static_cast<double>(k)};
            complex roots{std::cos(angle), std::sin(angle)};

            std::vector<complex> w(k);
            w[0] = {1, 0};
            for (size_t j = 1; j < k; j++) {
                w[j] = w[j - 1] * roots;
            }

            for (size_t i = 0; i < n; i += k * 2) {
                for (size_t j = 0; j < k; j++) {
                    complex even = data[i + j];
                    complex odd = data[i + j + k] * w[j];
                    data[i + j] = even + odd;
                    data[i + j + k] = even - odd;
                }
            }
        }
    }
    if (invert) {
        for (size_t i = 0; i < n; i++) {
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

    std::vector<complex> lhs_fft(n), rhs_fft(n);

    for (size_t i = 0; i < lhs.size(); i++) {
        lhs_fft[i] = {static_cast<double>(lhs[i]), 0.0};
    }
    for (size_t i = 0; i < rhs.size(); i++) {
        rhs_fft[i] = {static_cast<double>(rhs[i]), 0.0};
    }

    fft(lhs_fft);
    fft(rhs_fft);

    for (size_t i = 0; i < n; i++) {
        lhs_fft[i] *= rhs_fft[i];
    }

    fft(lhs_fft, true);

    std::vector<T> result(result_size);
    for (size_t i = 0; i < result_size; i++) {
        result[i] = static_cast<T>(std::lround(lhs_fft[i].real()));
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
};  // namespace fft

namespace ntt {
template <typename T>
T power(T base, T exp, T mod) {
    T result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

template <typename T>
T find_primitive_root(T mod) {
    if (mod == 998244353 || mod == 469762049 || mod == 167772161) {
        return 3;
    }
    std::vector<T> factors;
    T phi = mod - 1;
    T n = phi;
    for (T i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n > 1) {
        factors.push_back(n);
    }

    for (T i = 2; i < mod; i++) {
        bool is_primitive = true;
        for (T factor : factors) {
            if (power(i, phi / factor, mod) == 1) {
                is_primitive = false;
                break;
            }
        }
        if (is_primitive) {
            return i;
        }
    }
    return -1;
}

template <typename T>
void ntt(std::vector<T>& data, T mod, bool invert = false) {
    size_t n = data.size();
    if (n == 1) {
        return;
    }

    for (size_t i = 0, j = 0; i < n; i++) {
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

    T root = find_primitive_root(mod);

    for (size_t len = 2; len <= n; len <<= 1) {
        T w = invert ? power(root, mod - 1 - ((mod - 1) / len), mod)
                     : power(root, (mod - 1) / len, mod);

        for (size_t i = 0; i < n; i += len) {
            T wn = 1;
            for (size_t j = 0; j < len / 2; j++) {
                T even = data[i + j];
                T odd = (data[i + j + (len / 2)] * wn) % mod;

                data[i + j] = (even + odd) % mod;
                data[i + j + (len / 2)] = (even - odd + mod) % mod;

                wn = (wn * w) % mod;
            }
        }
    }

    if (invert) {
        T n_inv = power(static_cast<T>(n), mod - 2, mod);
        for (size_t i = 0; i < n; i++) {
            data[i] = (data[i] * n_inv) % mod;
        }
    }
}

template <typename T>
    requires std::is_integral_v<T>
std::vector<T> multiply(std::vector<T> const& lhs, std::vector<T> const& rhs,
                        T mod) {
    size_t result_size = lhs.size() + rhs.size() - 1;
    size_t n = 2;
    while (n < result_size) {
        n <<= 1;
    }

    std::vector<T> lhs_ntt(n), rhs_ntt(n);

    for (size_t i = 0; i < lhs.size(); i++) {
        lhs_ntt[i] = lhs[i] % mod;
    }
    for (size_t i = 0; i < rhs.size(); i++) {
        rhs_ntt[i] = rhs[i] % mod;
    }

    ntt(lhs_ntt, mod);
    ntt(rhs_ntt, mod);

    for (size_t i = 0; i < n; i++) {
        lhs_ntt[i] = (lhs_ntt[i] * rhs_ntt[i]) % mod;
    }

    ntt(lhs_ntt, mod, true);

    std::vector<T> result(result_size);
    for (size_t i = 0; i < result_size; i++) {
        result[i] = lhs_ntt[i];
    }
    return result;
}

template <typename T>
    requires std::is_integral_v<T>
std::vector<T> self_multiply(std::vector<T> const& vec, T mod) {
    size_t result_size = (2 * vec.size()) - 1;
    size_t n = 2;
    while (n < result_size) {
        n <<= 1;
    }

    std::vector<T> ntt_data(n);
    for (size_t i = 0; i < vec.size(); i++) {
        ntt_data[i] = vec[i] % mod;
    }

    ntt(ntt_data, mod);

    for (size_t i = 0; i < n; i++) {
        ntt_data[i] = (ntt_data[i] * ntt_data[i]) % mod;
    }

    ntt(ntt_data, mod, true);

    std::vector<T> result(result_size);
    for (size_t i = 0; i < result_size; i++) {
        result[i] = ntt_data[i];
    }
    return result;
}
};  // namespace ntt

namespace ntt_optimized {
template <typename T>
struct Barrett {
    T mod;
    __uint128_t m;

    explicit Barrett(T mod_)
        : mod(mod_), m((static_cast<__uint128_t>(-1)) / mod) {}

    T reduce(T x) const {
        T quotient = static_cast<T>((static_cast<__uint128_t>(m) * x) >> 64);
        T residue = x - (quotient * mod);
        return residue >= mod ? residue - mod : residue;
    }
};

template <typename T>
class NTT {
private:
    T mod;
    T primitive_root;
    Barrett<T> barrett;
    std::vector<std::vector<T>> roots;
    std::vector<std::vector<T>> inv_roots;

    T power(T base, T exp) const {
        T result = 1;
        while (exp > 0) {
            if (exp & 1) {
                result = barrett.reduce(result * base);
            }
            base = barrett.reduce(base * base);
            exp >>= 1;
        }
        return result;
    }

    T find_primitive_root() const {
        if (mod == 998244353 || mod == 469762049 || mod == 167772161) {
            return 3;
        }

        std::vector<T> factors;
        T phi = mod - 1;
        T n = phi;
        for (T i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                factors.push_back(i);
                while (n % i == 0) {
                    n /= i;
                }
            }
        }
        if (n > 1) {
            factors.push_back(n);
        }

        for (T i = 2; i < mod; i++) {
            bool is_primitive = true;
            for (T factor : factors) {
                if (power(i, phi / factor) == 1) {
                    is_primitive = false;
                    break;
                }
            }
            if (is_primitive) {
                return i;
            }
        }
        return 2;
    }

public:
    explicit NTT(T mod_)
        : mod(mod_), primitive_root(find_primitive_root()), barrett(mod_) {
        precompute_roots(20);
    }

    void precompute_roots(size_t max_log) {
        roots.resize(max_log + 1);
        inv_roots.resize(max_log + 1);

        for (size_t i = 0; i <= max_log; i++) {
            size_t len = 1 << i;
            roots[i].resize(len);
            inv_roots[i].resize(len);

            T w = power(primitive_root, (mod - 1) / (2 * len));
            T w_inv = power(w, mod - 2);

            roots[i][0] = inv_roots[i][0] = 1;
            for (size_t j = 1; j < len; j++) {
                roots[i][j] = barrett.reduce(roots[i][j - 1] * w);
                inv_roots[i][j] = barrett.reduce(inv_roots[i][j - 1] * w_inv);
            }
        }
    }

    void ntt(std::vector<T>& data, bool invert = false) {
        size_t n = data.size();
        if (n == 1) {
            return;
        }

        for (size_t i = 0, j = 0; i < n; i++) {
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

        for (size_t sz = 1, k = 0; sz < n; sz <<= 1, k++) {
            auto& w = invert ? inv_roots[k] : roots[k];

            for (size_t i = 0; i < n; i += 2 * sz) {
                for (size_t j = 0; j < sz; j++) {
                    T even = data[i + j];
                    T odd = barrett.reduce(data[i + j + sz] * w[j]);

                    data[i + j] =
                        (even + odd >= mod) ? even + odd - mod : even + odd;
                    data[i + j + sz] =
                        (even >= odd) ? even - odd : even - odd + mod;
                }
            }
        }

        if (invert) {
            T n_inv = power(n, mod - 2);
            for (size_t i = 0; i < n; i++) {
                data[i] = barrett.reduce(data[i] * n_inv);
            }
        }
    }

    std::vector<T> multiply(std::vector<T> const& lhs,
                            std::vector<T> const& rhs) {
        size_t result_size = lhs.size() + rhs.size() - 1;
        size_t n = 2;
        while (n < result_size) {
            n <<= 1;
        }

        std::vector<T> a(n), b(n);
        for (size_t i = 0; i < lhs.size(); i++) {
            a[i] = lhs[i] % mod;
        }
        for (size_t i = 0; i < rhs.size(); i++) {
            b[i] = rhs[i] % mod;
        }

        ntt(a);
        ntt(b);

        for (size_t i = 0; i < n; i++) {
            a[i] = barrett.reduce(a[i] * b[i]);
        }

        ntt(a, true);

        a.resize(result_size);
        return a;
    }
    std::vector<T> self_multiply(std::vector<T> const& vec) {
        size_t result_size = (2 * vec.size()) - 1;
        size_t n = 2;
        while (n < result_size) {
            n <<= 1;
        }

        std::vector<T> ntt_data(n);
        for (size_t i = 0; i < vec.size(); i++) {
            ntt_data[i] = vec[i] % mod;
        }

        ntt(ntt_data);

        for (size_t i = 0; i < n; i++) {
            ntt_data[i] = barrett.reduce(ntt_data[i] * ntt_data[i]);
        }

        ntt(ntt_data, true);

        std::vector<T> result(result_size);
        for (size_t i = 0; i < result_size; i++) {
            result[i] = ntt_data[i];
        }
        return result;
    }
};
};  // namespace ntt_optimized
