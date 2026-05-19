/*==== Copyright 2025 Azruine ====*/

#include <iostream>
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
}  // namespace

#include <algorithm>
#include <bitset>
#include <cmath>
#include <optional>
#include <print>
#include <unordered_map>
#include <vector>

namespace sieve {
template <typename T>
    requires std::is_integral_v<T>
class LinearSieve {
public:
    explicit LinearSieve(T n)
        : is_prime(n + 1, true), min_factor(n + 1, 0), prime_idx(n + 1, -1) {
        is_prime[0] = is_prime[1] = false;
        for (T i = 2; i <= n; i++) {
            if (is_prime[i]) {
                prime_idx[i] = as<T>(primes.size());
                primes.emplace_back(i);
                min_factor[i] = i;
            }
            for (T const& prime : primes) {
                if (prime > n / i || prime > min_factor[i]) {
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
    std::vector<T> const& get_prime_idx() const { return prime_idx; }

private:
    std::vector<T> primes;
    std::vector<bool> is_prime;
    std::vector<T> min_factor;
    std::vector<T> prime_idx;
};
}  // namespace sieve

template <size_t SIZE>
class XorRef {
    using int32_t_lim = std::numeric_limits<int32_t>;

    std::array<std::bitset<SIZE>, SIZE> matrix{};
    std::array<bool, SIZE> has_pivot{};
    std::array<int32_t, SIZE> timestamp{};

    void reduce(std::bitset<SIZE>& bitset) const { reduce_ts(bitset); }
    int32_t reduce_ts(std::bitset<SIZE>& bitset,
                      int32_t ts_lim = int32_t_lim::max()) const {
        int32_t max_ts = 0;
        for (size_t i = SIZE; i-- > 0;) {
            if (bitset.test(i) && has_pivot[i] && timestamp[i] <= ts_lim) {
                max_ts = std::max(max_ts, timestamp[i]);
                bitset ^= matrix[i];
            }
        }
        return max_ts;
    }
    size_t static get_msb(std::bitset<SIZE> const& bitset) {
        for (size_t i = SIZE; i-- > 0;) {
            if (bitset.test(i)) {
                return i;
            }
        }
        return SIZE;
    }

public:
    bool insert(std::bitset<SIZE> bitset) { return insert(bitset, 0); }
    bool insert(std::bitset<SIZE> bitset, int32_t ts) {
        while (bitset.any()) {
            auto pivot = get_msb(bitset);
            if (!has_pivot[pivot]) {
                matrix[pivot] = bitset;
                has_pivot[pivot] = true;
                timestamp[pivot] = ts;
                return true;
            }
            if (ts < timestamp[pivot]) {
                std::swap(bitset, matrix[pivot]);
                std::swap(ts, timestamp[pivot]);
            }
            bitset ^= matrix[pivot];
        }
        return false;
    }
    bool contains(std::bitset<SIZE> bitset) const {
        reduce_ts(bitset);
        return bitset.none();
    }

    int32_t query_max_ts(std::bitset<SIZE> bitset) const {
        int32_t max_ts = reduce_ts(bitset);
        return bitset.none() ? max_ts : -1;
    }
};

class Solver {
    constexpr static int32_t MAX = 1'000'010;
    constexpr static int32_t PRIME_LIM = 1'001;
    constexpr static size_t MAX_SIZE = 1 << 8;
    sieve::LinearSieve<int32_t> sieve{MAX};

    static bool is_square(int32_t x) {
        auto sqrt = as<int64_t>(std::sqrt(x));
        while (sqrt * sqrt < x) {
            sqrt += 1;
        }
        while (sqrt * sqrt > x) {
            sqrt -= 1;
        }
        return sqrt * sqrt == x;
    }

    template <size_t SIZE>
    struct PrimeProfile {
        using Rep =
            std::unordered_map<int32_t, std::pair<PrimeProfile<SIZE>, int32_t>>;
        std::bitset<SIZE> little_parts{};
        int32_t big_parts = 0;
    };
    template <size_t SIZE>
    using BigPartsRep = typename PrimeProfile<SIZE>::Rep;
    template <size_t SIZE>
    PrimeProfile<SIZE> make_profile(int32_t n) const {
        PrimeProfile<SIZE> ret;
        auto const& min_factor = sieve.get_min_factor();
        auto const& prime_idx = sieve.get_prime_idx();
        while (n > 1) {
            auto const prime = min_factor[n];
            auto cnt = 0;
            while (n % prime == 0) {
                n /= prime;
                cnt += 1;
            }
            if (cnt & 1) {
                if (prime < PRIME_LIM) {
                    ret.little_parts.set(prime_idx[prime]);
                } else {
                    ret.big_parts = prime;
                }
            }
        }
        return ret;
    }

    template <size_t SIZE>
    std::optional<std::pair<std::bitset<SIZE>, int32_t>> resolve(
        PrimeProfile<SIZE> const& profile, BigPartsRep<SIZE> const& rep,
        int32_t self_ts) const {
        if (profile.big_parts == 0) {
            return std::pair{profile.little_parts, 0};
        }
        auto it = rep.find(profile.big_parts);
        if (it == rep.end()) {
            return std::nullopt;
        }
        return std::pair{profile.little_parts ^ it->second.first.little_parts,
                         std::max(self_ts, it->second.second)};
    }

    template <size_t SIZE>
    int32_t compute_S(int32_t x, int32_t y_max) const {
        auto profile_x = make_profile<SIZE>(x);
        if (profile_x.little_parts.none() && profile_x.big_parts == 0) {
            return x;
        }

        XorRef<SIZE> basis;
        typename PrimeProfile<SIZE>::Rep rep;

        for (int32_t y = x + 1; y <= y_max; y++) {
            auto profile_y = make_profile<SIZE>(y);
            if (profile_y.big_parts == 0) {
                basis.insert(profile_y.little_parts, y);
            } else {
                auto it = rep.find(profile_y.big_parts);
                if (it == rep.end()) {
                    rep[profile_y.big_parts] = {profile_y, y};
                } else {
                    auto pair_little =
                        profile_y.little_parts ^ it->second.first.little_parts;
                    basis.insert(pair_little, it->second.second);
                    it->second = {profile_y, y};
                }
            }

            if (auto result = resolve(profile_x, rep, x); result) {
                if (result->first.none()) {
                    return std::max(y, result->second);
                }
                if (basis.contains(result->first)) {
                    return y;
                }
            }
        }
        return -1;
    }

    template <size_t SIZE>
    std::vector<int32_t> find_preimages(int32_t y) const {
        XorRef<SIZE> basis;
        BigPartsRep<SIZE> rep;
        std::vector<int32_t> res;

        for (int32_t x = y - 1; x >= 1; x--) {
            int32_t next = x + 1;
            auto profile_next = make_profile<SIZE>(next);
            if (profile_next.big_parts == 0) {
                basis.insert(profile_next.little_parts, next);
            } else {
                auto it = rep.find(profile_next.big_parts);
                if (it == rep.end()) {
                    rep[profile_next.big_parts] = {profile_next, next};
                } else {
                    auto pair_little = profile_next.little_parts
                                       ^ it->second.first.little_parts;
                    int32_t pair_ts = it->second.second;
                    basis.insert(pair_little, pair_ts);
                    it->second = {profile_next, next};
                }
            }

            auto profile_x = make_profile<SIZE>(x);
            if (auto result = resolve(profile_x, rep, x); result) {
                if (result->first.none()) {
                    continue;
                }
                int32_t basis_ts = basis.query_max_ts(result->first);
                if (basis_ts < 0) {
                    continue;
                }
                int32_t total_ts = std::max(basis_ts, result->second);
                if (total_ts == y) {
                    res.emplace_back(x);
                }
            }
        }

        if (is_square(y)) {
            res.emplace_back(y);
        }
        std::ranges::sort(res);
        return res;
    }

public:
    void solve() {
        int32_t y = 0;
        std::cin >> y;
        auto res = find_preimages<MAX_SIZE>(y);
        std::println("{}", res.size());
        for (size_t i = 0; i < res.size(); i++) {
            std::print("{}{}", res[i], (i + 1 == res.size()) ? '\n' : ' ');
        }
    }
};

int main() {
    fastio();
    Solver solver;
    solver.solve();
    return 0;
}
