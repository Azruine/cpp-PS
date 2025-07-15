/*==== Copyright 2025 Azruine ====*/

#include <map>
#include <queue>
#include <random>
#include <set>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

// Globsal variable for storing prime number list
std::set<uint64_t> prime_set;

// Random number generator
std::mt19937 engine(std::random_device{}());
std::uniform_int_distribution<int32_t> distribution(1, (1UL << 16) - 1);

// Generating prime number list less than 1<<16 using sieve of Eratosthenes
void sieve() {
    std::vector<bool> is_prime_65535(1 << 16, true);

    is_prime_65535[0] = false;
    is_prime_65535[1] = false;

    for (size_t p = 2; p * p < 1 << 16; p++) {
        if (is_prime_65535[p]) {
            for (size_t i = p * p; i < 1 << 16; i += p) {
                is_prime_65535[i] = false;
            }
        }
    }

    for (size_t p = 2; p < 1 << 16; p++) {
        if (is_prime_65535[p]) {
            prime_set.insert(p);
        }
    }
}

// Modular multiplication using 128 bit integer to prevent overflow in 64 bit
// integer
uint64_t modMul128(uint64_t a, uint64_t b, uint64_t m) {
    a %= m;
    b %= m;
    __uint128_t a128 = a;
    __uint128_t b128 = b;
    __uint128_t m128 = m;
    return (uint64_t)((a128 * b128) % m128);
}

// Modular exponentiation using 128 bit integer to prevent overflow in 64 bit
// integer
uint64_t modPow128(uint64_t x, uint64_t y, uint64_t m) {
    x %= m;

    __uint128_t x128 = x;
    __uint128_t m128 = m;
    __uint128_t res = 1;

    while (y > 0) {
        if (y % 2 == 1) {
            res = (res * x128) % m128;
        }
        x128 = (x128 * x128) % m128;
        y >>= 1;
    }

    return (uint64_t)res;
}

// Miller-Rabin primality test key algorithm
bool mr_prime(uint64_t n, uint64_t a) {
    // Special Cases
    if (n == 1) return false;
    if (n == 2) return true;

    uint64_t k = n - 1;
    uint64_t temp = 0;

    while (true) {
        temp = modPow128(a, k, n);

        if (temp == n - 1) {
            return true;
        }

        if (k & 1) {
            if (temp == 1 || temp == n - 1) {
                return true;
            } else {
                return false;
            }
        }

        k >>= 1;
    }
}

// Deterministic primality test using Miller-Rabin
bool isPrime(uint64_t n) {
    // Base list for Miller-Rabin primality test less than 2^64
    // vector<int> base = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    std::vector<size_t> base = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    if (prime_set.contains(n)) return true;

    if (n < 1UL << 16) {
        for (size_t i = 2; i * i <= n; i++) {
            if (prime_set.contains(i)) {
                while (n % i == 0) {
                    {
                        return false;
                    }
                }
            }
        }
    }

    for (auto a : base)
        if (!mr_prime(n, a)) {
            return false;
        }

    prime_set.insert(n);
    return true;
}

// Euclidean algorithm
uint64_t gcd(uint64_t x, uint64_t y) {
    while (y != 0) {
        uint64_t r = x % y;
        x = y;
        y = r;
    }
    return x;
}

uint64_t gcdNew(uint64_t x, uint64_t y) {
    uint64_t t_0 = x, t_1 = y, t_2 = 1;
    while (!(t_0 & 1) && !(t_1 & 1)) {
        t_0 >>= 1;
        t_1 >>= 1;
        t_2 <<= 1;
    }
    while (t_1 != 0) {
        while (!(t_0 & 1)) {
            t_0 >>= 1;
        }
        while (!(t_1 & 1)) {
            t_1 >>= 1;
        }
        if (t_0 >= t_1) {
            uint64_t temp = t_0;
            t_0 = t_1;
            t_1 = temp % t_1;
        } else {
            t_1 %= t_0;
        }
    }
    return t_0 * t_2;
}

// f(x) = x^2 + c
uint64_t functionF(uint64_t x, uint64_t n) {
    // int c = distribution(engine);
    constexpr static uint64_t c = 5;
    return modMul128(x, x, n) + c;
}

// Pollard's rho algorithm
std::pair<uint64_t, uint64_t> pollard_rho(uint64_t n,
                                         std::map<uint64_t, int>& factors_set) {
    // If n is 1, return (1, 1)
    if (n == 1) {
        return {1, 1};
    }

    // If n is prime, return (n, 1)
    if (isPrime(n)) {
        factors_set[n]++;
        return {n, 1};
    }

    // 	// Remove primes in the prime set before factoring to reduce calculation
    // 	for (auto i : prime_set)
    // 	{
    // 		if (n < i)
    // 			break;
    // 		if (n % i == 0)
    // 			return make_pair(i, n / i);
    // 	}

    uint64_t x = 0, y = 0, t = 30, prd = 2, i = 1, q;
    while (t++ % 40 || gcdNew(prd, n) == 1) {
        if (x == y) x = ++i, y = functionF(x, n);
        if ((q = modMul128(prd, std::max(x, y) - std::min(x, y), n))) {
            prd = q;
        }
        x = functionF(x, n), y = functionF(functionF(y, n), n);
    }

    uint64_t d = gcdNew(prd, n);
    if (d == n) {
        return {1, 1};
    }
    return {d, n / d};

    // // Initialize x, y, d
    // uint64_t x = distribution(engine);
    // uint64_t y = x;
    // uint64_t d;

    // // Pollard's rho algorithm
    // while (true)
    // {
    // 	x = functionF(x, n);
    // 	y = functionF(functionF(y, n), n);

    // 	if (x == y)
    // 	{
    // 		x = distribution(engine);
    // 		y = x;
    // 		continue;
    // 	}

    // 	if (x > y)
    // 		d = gcdNew(x - y, n);
    // 	else
    // 		d = gcdNew(y - x, n);

    // 	if (d != 1 && d != n)
    // 		return make_pair(d, n / d);
    // }
}

// Factorization function using Pollard rho algorithm
void factorize(uint64_t n, std::map<uint64_t, int>& factors_set) {
    std::pair<uint64_t, uint64_t> temp;
    std::queue<uint64_t> que;

    que.push(n);

    while (!que.empty()) {
        uint64_t dividend = que.front();
        que.pop();
        temp = pollard_rho(dividend, factors_set);
        if (temp.second != 1 && temp.first != 1) {
            que.push(temp.first);
            que.push(temp.second);
        }
    }
}
