#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                         \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

void sieve(std::vector<int> &primes, std::vector<int> &minDiv, const int &MAX)
{
    minDiv.assign(MAX + 1, -1);
    minDiv[1] = 1;
    for (int i = 2; i <= MAX; i++)
    {
        if (minDiv[i] == -1)
        {
            primes.emplace_back(i);
            minDiv[i] = i;
        }
        for (auto &p : primes)
        {
            if (i * p > MAX)
                break;
            minDiv[i * p] = p;
            if (i % p == 0)
                break;
        }
    }
    return;
}

class Solver
{
private:
    const int MAX = 31;
    std::vector<int> primes;
    std::vector<int> minPrimes;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        sieve(primes, minPrimes, MAX);
        int size = static_cast<int>(primes.size());
        std::vector<ull> primeAccMul(size, 1);
        std::inclusive_scan(primes.begin(), primes.end(), primeAccMul.begin(), [&](ull acc, int x){return acc * x;}, (ull)1);
        int x;
        while (std::cin >> x)
        {
            if (!x)
                break;
            printPrimeBase(x, size, primeAccMul);
            std::cout << '\n';
        }
        return;
    }
    void printPrimeBase(int n, int size, const std::vector<ull> &primeAccMul)
    {
        std::vector<int> primeBase(size, 0);
        int n0 = n;
        for (int i = size - 1; i >= 0; i--)
        {
            primeBase[i] = n / primeAccMul[i];
            n %= primeAccMul[i];
        }
        bool isFirst = true;
        std::cout << n0;
        if (n)
        {
            std::cout << " = 1";
            isFirst = false;
        }
        for (int i = 0; i < size; i++)
        {
            if (primeBase[i] == 0)
                continue;
            std::cout << " " << "+="[isFirst] << " ";
            isFirst = false;
            std::cout << primeBase[i];
            for (int j = 0; j <= i; j++)
                std::cout << "*" << primes[j];
        }
        return;
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}