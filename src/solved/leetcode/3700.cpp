/*==== Copyright 2025 Azruine ====*/

#include <ranges>
#include <utility>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
struct Range {
    template <typename Sentinel>
    constexpr auto operator()(Sentinel sentinel) const noexcept {
        return std::views::iota(static_cast<Sentinel>(0), sentinel);
    }
    template <typename Start, typename Sentinel>
    constexpr auto operator()(Start start, Sentinel sentinel) const noexcept {
        return std::views::iota(start, sentinel);
    }
    template <typename Start, typename Sentinel, typename Step>
    constexpr auto operator()(Start start, Sentinel sentinel,
                              Step step) const noexcept {
        return std::views::iota(start, sentinel) | std::views::stride(step);
    }
};
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
constexpr Range _iota{};
#pragma GCC diagnostic pop
}  // namespace

#include <vector>

constexpr int64_t MOD = 1'000'000'007;

int64_t norm(int64_t val) {
    val %= MOD;
    if (val < 0) {
        val += MOD;
    }
    return val;
}

int64_t mod_pow(int64_t base, int64_t exp) {
    int64_t ret = 1;
    while (exp > 0) {
        if (exp & 1) {
            ret = ret * base % MOD;
        }
        base = base * base % MOD;
        exp >>= 1;
    }
    return ret;
}

int64_t mod_inv(int64_t val) { return mod_pow(val, MOD - 2); }

std::vector<int64_t> berlekamp_massey(std::vector<int64_t> const& seq) {
    std::vector<int64_t> cur(1, 1);
    std::vector<int64_t> backup(1, 1);
    int64_t prev_rec = 1;
    size_t rec = 0;
    size_t shift = 1;
    for (size_t idx = 0; idx < seq.size(); idx++) {
        int64_t disc = 0;
        for (size_t pos = 0; pos <= rec; pos++) {
            disc = (disc + cur[pos] * seq[idx - pos]) % MOD;
        }
        if (disc == 0) {
            shift++;
            continue;
        }
        std::vector<int64_t> prev = cur;
        int64_t coef = disc * mod_inv(prev_rec) % MOD;
        if (cur.size() < backup.size() + shift) {
            cur.resize(backup.size() + shift);
        }
        for (size_t pos = 0; pos < backup.size(); pos++) {
            cur[pos + shift] = norm(cur[pos + shift] - coef * backup[pos]);
        }
        if (2 * rec <= idx) {
            rec = idx + 1 - rec;
            backup = std::move(prev);
            prev_rec = disc;
            shift = 1;
        } else {
            shift++;
        }
    }
    cur.erase(cur.begin());
    for (auto& coef : cur) {
        coef = norm(-coef);
    }
    return cur;
}

std::vector<int64_t> combine_poly(std::vector<int64_t> const& lhs,
                                  std::vector<int64_t> const& rhs,
                                  std::vector<int64_t> const& rec) {
    size_t deg = rec.size();
    std::vector<int64_t> tmp(2 * deg - 1, 0);
    for (size_t row = 0; row < deg; row++) {
        for (size_t col = 0; col < deg; col++) {
            tmp[row + col] = (tmp[row + col] + lhs[row] * rhs[col]) % MOD;
        }
    }
    size_t idx = 2 * deg - 1;
    while (idx-- > deg) {
        int64_t val = tmp[idx];
        if (val == 0) {
            continue;
        }
        for (size_t pos = 0; pos < deg; pos++) {
            tmp[idx - 1 - pos] = (tmp[idx - 1 - pos] + val * rec[pos]) % MOD;
        }
    }
    tmp.resize(deg);
    return tmp;
}

int64_t linear_nth(std::vector<int64_t> const& init,
                   std::vector<int64_t> const& rec, size_t nth) {
    if (nth < init.size()) {
        return init[nth];
    }
    size_t deg = rec.size();
    if (deg == 0) {
        return 0;
    }
    std::vector<int64_t> ret_poly(deg, 0);
    std::vector<int64_t> base_poly(deg, 0);
    ret_poly[0] = 1;
    if (deg == 1) {
        base_poly[0] = rec[0];
    } else {
        base_poly[1] = 1;
    }
    while (nth > 0) {
        if (nth & 1) {
            ret_poly = combine_poly(ret_poly, base_poly, rec);
        }
        base_poly = combine_poly(base_poly, base_poly, rec);
        nth >>= 1;
    }
    int64_t ret = 0;
    for (size_t idx = 0; idx < deg; idx++) {
        ret = (ret + ret_poly[idx] * init[idx]) % MOD;
    }
    return ret;
}

std::vector<int64_t> make_seq(size_t val_cnt, size_t need) {
    std::vector<int64_t> seq;
    std::vector<int64_t> inc(val_cnt + 1, 0);
    std::vector<int64_t> dec(val_cnt + 1, 0);
    seq.reserve(need);
    seq.emplace_back(val_cnt);
    for (size_t val = 1; val <= val_cnt; val++) {
        inc[val] = val - 1;
        dec[val] = val_cnt - val;
    }
    auto sum_state = [&]() {
        int64_t ret = 0;
        for (size_t val = 1; val <= val_cnt; val++) {
            ret = (ret + inc[val] + dec[val]) % MOD;
        }
        return ret;
    };
    seq.emplace_back(sum_state());
    for (size_t len = 3; len <= need; len++) {
        std::vector<int64_t> next_inc(val_cnt + 1, 0);
        std::vector<int64_t> next_dec(val_cnt + 1, 0);
        int64_t pref = 0;
        for (size_t val = 1; val <= val_cnt; val++) {
            next_inc[val] = pref;
            pref = (pref + dec[val]) % MOD;
        }
        int64_t suff = 0;
        for (size_t val = val_cnt; val > 0; val--) {
            next_dec[val] = suff;
            suff = (suff + inc[val]) % MOD;
        }
        inc = std::move(next_inc);
        dec = std::move(next_dec);
        seq.emplace_back(sum_state());
    }
    return seq;
}

class Solution {
public:
    int32_t zigZagArrays(int32_t n, int32_t l, int32_t r) {
        size_t val_cnt = r - l + 1;
        size_t need = 4 * val_cnt + 10;
        size_t target = n - 1;
        std::vector<int64_t> seq = make_seq(val_cnt, need);
        if (target < seq.size()) {
            return seq[target];
        }
        std::vector<int64_t> rec = berlekamp_massey(seq);
        std::vector<int64_t> init;
        init.reserve(rec.size());
        for (size_t idx = 0; idx < rec.size(); idx++) {
            init.emplace_back(seq[idx]);
        }
        return linear_nth(init, rec, target);
    }
};
