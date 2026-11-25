#include <bits/stdc++.h>
using std::cin, std::cout, std::vector;
using namespace std::views;

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
class Sieve {
public:
    explicit Sieve(T n) : is_p(n + 1, true), minf(n + 1, 0) {
        is_p[0] = is_p[1] = false;
        for (T i = 2; i <= n; i++) {
            if (is_p[i]) {
                ps.push_back(i);
                minf[i] = i;
            }
            for (T const& prime : ps) {
                if (prime * i > n || prime > minf[i]) break;
                is_p[prime * i] = false;
                minf[prime * i] = prime;
            }
        }
    }
    vector<T> const& get_primes() const { return ps; }
    vector<bool> const& get_is_prime() const { return is_p; }
    vector<T> const& get_min_factor() const { return minf; }

private:
    vector<T> ps;
    vector<bool> is_p;
    vector<T> minf;
};

Sieve<int64_t> sieve(1'000'010);

static int64_t sqrt(int64_t x) {
    auto ret = as<int64_t>(std::sqrt(x));
    while (ret * ret < x) ret++;
    while (ret * ret > x) ret--;
    return ret;
}

int64_t cnt(int64_t x) {
    if (x < 2) return 0;
    int64_t rt = sqrt(x);
    vector<int32_t> sml(rt + 1);
    vector<int64_t> big(rt + 1), li(rt);
    for (auto i : iota(1L, rt + 1)) {
        sml[i] = as<int32_t>(i) - 1;
        big[i] = (x / i) - 1;
        li[i - 1] = i;
    }
    int64_t l_cnt = 0;
    auto& ps = sieve.get_primes();
    auto& minf = sieve.get_min_factor();
    for (auto [i, p] : ps | enumerate) {
        if (p > rt) break;
        if (p * p <= rt) {
            size_t rem = 0;
            for (auto l : li) {
                if (l != 1 && minf[l] <= p) continue;
                int64_t next = l * p;
                int64_t left = (next <= rt) ? big[next] : sml[x / next];
                big[l] -= (left - l_cnt);
                li[rem] = l;
                rem += 1;
            }
            li.resize(rem);
            int64_t val = rt;
            for (int64_t q = rt / p; q >= p; q--) {
                int64_t rmv = sml[q] - l_cnt;
                int64_t blk = q * p;
                while (val >= blk) sml[val--] -= as<int32_t>(rmv);
            }
            l_cnt += 1;
        } else {
            int64_t s = x / (p * p);
            for (auto n : ps | drop(i + 1)) {
                if (n > s) break;
                big[n] -= sml[x / (p * n)] - l_cnt;
            }
            big[1] -= big[p] - l_cnt;
            l_cnt += 1;
        }
    }
    return big[1];
}

int main() {
    fastio();
    int64_t t, x;
    cin >> t;
    while (cin >> x) cout << cnt(x) << '\n';
}