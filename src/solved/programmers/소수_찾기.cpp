#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

std::unordered_set<int> sieve()
{
    constexpr int MAX = 10'000'010;
    std::vector<int> lowestPrime(MAX, 0);
    std::vector<int> primes;
    lowestPrime[1] = 1;
    for (int i = 2; i < MAX; i++)
    {
        if (lowestPrime[i] == 0)
        {
            primes.push_back(i);
            lowestPrime[i] = i;
        }
        for (auto &p : primes)
        {
            if (p > lowestPrime[i] || i * p >= MAX)
                break;
            lowestPrime[i * p] = p;
            if (i % p == 0)
                break;
        }
    }
    return std::unordered_set(primes.begin(), primes.end());
}

int solution(string numbers) {
    int answer = 0;
    auto primes = sieve();
    std::unordered_set<int> p;
    int n = numbers.length();
    for (int l = 1; l <= n; l++)
    {
        std::string com = numbers;
        std::sort(com.begin(), com.end());
        do
        {
            std::string substr = com.substr(0, l);
            do
            {
                p.insert(std::stoi(substr));
            } while (std::next_permutation(substr.begin(), substr.end()));
        } while (std::next_permutation(com.begin(), com.end()));
    }
    for (auto &i : p)
        if (primes.find(i) != primes.end())
            answer++;
    return answer;
}