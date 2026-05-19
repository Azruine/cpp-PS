/*==== Copyright 2025 Azruine ====*/

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
        if (lhs.size() == 0 || rhs.size() == 0) {
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
        if (vec.size() == 0) {
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

namespace ntt {
template <typename T>
class Barrett {
    T mod;
    __uint128_t m;

public:
    explicit Barrett(T mod_)
        : mod(mod_), m((static_cast<__uint128_t>(1) << 64) / mod) {}
    T reduce(__uint128_t x) const {
        T quotient = static_cast<T>((m * x) >> 64);
        T residue =
            static_cast<T>(x - (static_cast<__uint128_t>(quotient) * mod));
        return residue >= mod ? residue - mod : residue;
    }
    T reduce(T lhs, T rhs) const {
        __uint128_t x = static_cast<__uint128_t>(lhs) * rhs;
        return reduce(x);
    }
};

template <typename T>
class NTT {
    T mod;
    size_t cache_size = 0;
    Barrett<T> barrett;
    T primitive_root;
    std::vector<T> roots, inv_roots;

    void fill_roots(size_t n) {
        if (n <= cache_size) {
            return;
        }
        cache_size = n;
        roots.resize(n >> 1);
        inv_roots.resize(n >> 1);

        T w = power(primitive_root, (mod - 1) / n);
        T w_inv = power(w, mod - 2);

        roots[0] = inv_roots[0] = 1;

        for (size_t i = 1; i < (n >> 1); i++) {
            roots[i] = barrett.reduce(roots[i - 1], w);
            inv_roots[i] = barrett.reduce(inv_roots[i - 1], w_inv);
        }
    }

    T power(T base, T exp) const {
        T result = 1;
        while (exp > 0) {
            if (exp & 1) {
                result = barrett.reduce(result, base);
            }
            base = barrett.reduce(base, base);
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
        : mod(mod_), barrett(mod_), primitive_root(find_primitive_root()) {}

    void ntt(std::vector<T>& data, bool invert = false) {
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

        auto const& roots_table = invert ? inv_roots : roots;

        for (size_t k = 1; k < n; k <<= 1) {
            size_t step = cache_size / (k << 1);
            for (size_t i = 0; i < n; i += (k << 1)) {
                size_t idx = 0;
                for (size_t j = 0; j < k; j++) {
                    T even = data[i + j];
                    T odd = barrett.reduce(data[i + j + k], roots_table[idx]);
                    T sum = even + odd;
                    sum = sum - (sum >= mod ? mod : 0);
                    T diff = even - odd + (even < odd ? mod : 0);
                    data[i + j] = sum;
                    data[i + j + k] = diff;
                    idx += step;
                }
            }
        }

        if (invert) {
            T n_inv = power(static_cast<T>(n), mod - 2);
            for (size_t i = 0; i < n; i++) {
                data[i] = barrett.reduce(data[i], n_inv);
            }
        }
    }

    std::vector<T> multiply(std::vector<T> const& lhs,
                            std::vector<T> const& rhs) {
        if (lhs.size() == 0 || rhs.size() == 0) {
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
                    T prod = barrett.reduce(lhs[i], rhs[j]);
                    T sum = ret[i + j] + prod;
                    ret[i + j] = sum - ((sum >= mod) ? mod : 0);
                }
            }
            return ret;
        }
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

        ntt(lhs_ntt);
        ntt(rhs_ntt);

        for (size_t i = 0; i < n; i++) {
            lhs_ntt[i] = barrett.reduce(lhs_ntt[i], rhs_ntt[i]);
        }

        ntt(lhs_ntt, true);

        lhs_ntt.resize(result_size);
        return lhs_ntt;
    }

    std::vector<T> self_multiply(std::vector<T> const& vec) {
        if (vec.size() == 0) {
            return {};
        }
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
            ntt_data[i] = barrett.reduce(ntt_data[i], ntt_data[i]);
        }

        ntt(ntt_data, true);

        ntt_data.resize(result_size);
        return ntt_data;
    }
};
};  // namespace ntt

namespace ntt_optimized {
template <typename T>
constexpr T as(auto&& x) noexcept {
    return static_cast<T>(decltype(x)(x));
}

template <uint32_t MOD = 0>
class Montgomery {
    static constexpr bool DYNAMIC = (MOD == 0);
    struct empty {};

    std::conditional_t<DYNAMIC, uint32_t, empty> mod_dyn;
    std::conditional_t<DYNAMIC, uint32_t, empty> mod_inv_dyn;
    std::conditional_t<DYNAMIC, uint32_t, empty> r2_dyn;

    static constexpr uint32_t calc_mod_inv(uint32_t m) {
        uint32_t inv = 1;
        for (int i = 0; i < 5; i++) {
            inv *= 2u - m * inv;
        }
        return 0u - inv;
    }
    static constexpr uint32_t calc_r2(uint32_t m) {
        return static_cast<uint32_t>((static_cast<__uint128_t>(1) << 64) % m);
    }

public:
    Montgomery()
        requires(!DYNAMIC)
    = default;
    explicit Montgomery(uint32_t m)
        requires(DYNAMIC)
        : mod_dyn(m), mod_inv_dyn(calc_mod_inv(m)), r2_dyn(calc_r2(m)) {}

    constexpr uint32_t mod() const {
        if constexpr (DYNAMIC) {
            return mod_dyn;
        } else {
            return MOD;
        }
    }
    constexpr uint32_t mod_inv() const {
        if constexpr (DYNAMIC) {
            return mod_inv_dyn;
        } else {
            return calc_mod_inv(MOD);
        }
    }
    constexpr uint32_t r2() const {
        if constexpr (DYNAMIC) {
            return r2_dyn;
        } else {
            return calc_r2(MOD);
        }
    }

    uint32_t reduce(uint64_t x) const {
        auto t = (uint32_t)x * mod_inv();
        auto r = (uint32_t)((x + (uint64_t)t * mod()) >> 32);
        return r - (r >= mod() ? mod() : 0);
    }

    uint32_t reduce_lazy(uint64_t x) const {
        auto temp = as<uint32_t>(x) * mod_inv();
        return as<uint32_t>((x + as<uint64_t>(temp) * MOD) >> 32);
    }

    uint32_t mul(uint32_t lhs, uint32_t rhs) const {
        return reduce(as<uint64_t>(lhs) * rhs);
    }

    uint32_t mul_lazy(uint32_t lhs, uint32_t rhs) const {
        return reduce_lazy(as<uint64_t>(lhs) * rhs);
    }

    uint32_t to_mont(uint32_t x) const { return mul(x, r2()); }

    uint32_t from_mont(uint32_t x) const { return reduce(x); }
};

template <uint32_t MOD = 0>
class NTT {
    static constexpr bool DYNAMIC = (MOD == 0);
    struct empty {};
    std::conditional_t<DYNAMIC, uint32_t, empty> mod_dyn;

    constexpr uint32_t mod() const {
        if constexpr (DYNAMIC) {
            return mod_dyn;
        } else {
            return MOD;
        }
    }
    constexpr uint32_t mod_2() const { return mod() << 1; }

    Montgomery<MOD> mont;
    size_t cache_size = 0;
    uint32_t primitive_root;
    std::vector<uint32_t> roots, inv_roots;

    void fill_roots(size_t n) {
        if (n <= cache_size) {
            return;
        }
        cache_size = n;
        roots.resize(n >> 1);
        inv_roots.resize(n >> 1);

        uint32_t w = power(primitive_root, (MOD - 1) / n);
        uint32_t w_inv = power(w, MOD - 2);

        uint32_t w_m = mont.to_mont(w);
        uint32_t wi_m = mont.to_mont(w_inv);

        roots[0] = inv_roots[0] = mont.to_mont(1);

        for (size_t i = 1; i < (n >> 1); i++) {
            roots[i] = mont.mul(roots[i - 1], w_m);
            inv_roots[i] = mont.mul(inv_roots[i - 1], wi_m);
        }
    }

    uint32_t power(uint32_t base, uint32_t exp) const {
        uint32_t result = mont.to_mont(1);
        uint32_t b = mont.to_mont(base);
        while (exp) {
            if (exp & 1) {
                result = mont.mul(result, b);
            }
            b = mont.mul(b, b);
            exp >>= 1;
        }
        return mont.from_mont(result);
    }

    uint32_t find_primitive_root() const {
        if (MOD == 998244353 || MOD == 469762049 || MOD == 167772161) {
            return 3;
        }

        std::vector<uint32_t> factors;
        uint32_t phi = MOD - 1;
        uint32_t n = phi;
        for (uint32_t i = 2; i * i <= n; i++) {
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

        for (uint32_t i = 2; i < MOD; i++) {
            bool is_primitive = true;
            for (uint32_t factor : factors) {
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

    void ntt_for(std::vector<uint32_t>& data) {
        size_t n = data.size();
        for (size_t k = n >> 1; k > 1; k >>= 1) {
            size_t step = cache_size / (k << 1);
            for (size_t i = 0; i < n; i += (k << 1)) {
                size_t idx = 0;
                for (size_t j = 0; j < k; j++) {
                    uint32_t a = data[i + j];
                    uint32_t b = data[i + j + k];
                    uint32_t sum = a + b;
                    sum -= (sum >= mod_2()) ? mod_2() : 0;
                    uint32_t diff = a + mod_2() - b;
                    data[i + j] = sum;
                    data[i + j + k] = mont.mul_lazy(diff, roots[idx]);
                    idx += step;
                }
            }
        }
        for (size_t i = 0; i < n; i += 2) {
            uint32_t a = data[i];
            uint32_t b = data[i + 1];
            uint32_t sum = a + b;
            sum -= (sum >= mod_2()) ? mod_2() : 0;
            uint32_t diff = a + mod_2() - b;
            diff -= (diff >= mod_2()) ? mod_2() : 0;
            data[i] = sum;
            data[i + 1] = diff;
        }
    }
    void ntt_inv(std::vector<uint32_t>& data) {
        size_t n = data.size();
        for (size_t i = 0; i < n; i += 2) {
            uint32_t a = data[i];
            uint32_t b = data[i + 1];
            uint32_t sum = a + b;
            sum -= (sum >= mod_2()) ? mod_2() : 0;
            uint32_t diff = a + mod_2() - b;
            diff -= (diff >= mod_2()) ? mod_2() : 0;
            data[i] = sum;
            data[i + 1] = diff;
        }
        for (size_t k = 2; k < n; k <<= 1) {
            size_t step = cache_size / (k << 1);
            for (size_t i = 0; i < n; i += (k << 1)) {
                size_t idx = 0;
                for (size_t j = 0; j < k; j++) {
                    uint32_t even = data[i + j];
                    uint32_t odd =
                        mont.mul_lazy(data[i + j + k], inv_roots[idx]);
                    uint32_t sum = even + odd;
                    sum -= (sum >= mod_2()) ? mod_2() : 0;
                    uint32_t diff = even + mod_2() - odd;
                    diff -= (diff >= mod_2()) ? mod_2() : 0;
                    data[i + j] = sum;
                    data[i + j + k] = diff;
                    idx += step;
                }
            }
        }
        uint32_t n_inv = power(as<uint32_t>(n), MOD - 2);
        uint32_t n_inv_m = mont.to_mont(n_inv);
        for (size_t i = 0; i < n; i++) {
            data[i] = mont.mul(data[i], n_inv_m);
        }
    }

public:
    NTT()
    requires(!DYNAMIC) : mont(), primitive_root(find_primitive_root()) {
        if constexpr (!DYNAMIC) {
            static_assert(MOD < (1U << 30), "MOD must be < 2^30");
            static_assert(MOD % 2 == 1, "MOD must be odd");
        }
    }
    explicit NTT(uint32_t m)
        requires(DYNAMIC)
        : mod_dyn(m), mont(m), primitive_root(find_primitive_root()) {
        if (m >= (1U << 30) || (m & 1) == 0) {
            throw std::invalid_argument("NTT: invalid mod");
        }
    }

    void ntt(std::vector<uint32_t>& data, bool invert = false) {
        size_t n = data.size();
        if (n == 1) {
            return;
        }
        fill_roots(n);
        invert ? ntt_inv(data) : ntt_for(data);
    }

    std::vector<uint32_t> multiply(std::vector<uint32_t> const& lhs,
                                   std::vector<uint32_t> const& rhs) {
        if (lhs.size() == 0 || rhs.size() == 0) {
            return {};
        }
        constexpr size_t NAIVE_THRESHOLD = 64;
        if (lhs.size() * rhs.size() <= NAIVE_THRESHOLD * NAIVE_THRESHOLD) {
            std::vector<uint32_t> ret(lhs.size() + rhs.size() - 1, 0);
            for (size_t i = 0; i < lhs.size(); i++) {
                if (lhs[i] == 0) {
                    continue;
                }
                for (size_t j = 0; j < rhs.size(); j++) {
                    uint64_t prod = as<uint64_t>(lhs[i]) * rhs[j];
                    uint64_t sum = ret[i + j] + prod;
                    ret[i + j] = as<uint32_t>(sum % MOD);
                }
            }
            return ret;
        }

        size_t result_size = lhs.size() + rhs.size() - 1;
        size_t n = 2;
        while (n < result_size) {
            n <<= 1;
        }

        std::vector<uint32_t> lhs_ntt(n), rhs_ntt(n);
        for (size_t i = 0; i < lhs.size(); i++) {
            lhs_ntt[i] = mont.to_mont(lhs[i] % MOD);
        }
        for (size_t i = 0; i < rhs.size(); i++) {
            rhs_ntt[i] = mont.to_mont(rhs[i] % MOD);
        }

        ntt(lhs_ntt);
        ntt(rhs_ntt);

        for (size_t i = 0; i < n; i++) {
            lhs_ntt[i] = mont.mul_lazy(lhs_ntt[i], rhs_ntt[i]);
        }

        ntt(lhs_ntt, true);

        lhs_ntt.resize(result_size);
        for (size_t i = 0; i < result_size; i++) {
            lhs_ntt[i] = mont.from_mont(lhs_ntt[i]);
        }
        return lhs_ntt;
    }

    std::vector<uint32_t> self_multiply(std::vector<uint32_t> const& vec) {
        if (vec.size() == 0) {
            return {};
        }
        size_t result_size = (2 * vec.size()) - 1;
        size_t n = 2;
        while (n < result_size) {
            n <<= 1;
        }

        std::vector<uint32_t> ntt_data(n);
        for (size_t i = 0; i < vec.size(); i++) {
            ntt_data[i] = mont.to_mont(vec[i] % MOD);
        }

        ntt(ntt_data);

        for (size_t i = 0; i < n; i++) {
            ntt_data[i] = mont.mul_lazy(ntt_data[i], ntt_data[i]);
        }

        ntt(ntt_data, true);

        ntt_data.resize(result_size);
        for (size_t i = 0; i < result_size; i++) {
            ntt_data[i] = mont.from_mont(ntt_data[i]);
        }
        return ntt_data;
    }
};
};  // namespace ntt_optimized
