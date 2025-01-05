#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define fastio                             \
	std::ios_base::sync_with_stdio(false); \
	std::cin.tie(NULL);                    \
	std::cout.tie(NULL);

class Solver
{
private:
	ll x, y;
	ll cardinalCost, diagonalCost;

public:
	Solver()
	{
		std::cin >> x >> y;
		std::cin >> cardinalCost >> diagonalCost;
	}
	void solve()
	{
		ll ans1 = std::abs(x) * cardinalCost + std::abs(y) * cardinalCost;
		ll ans2 = std::min(x, y) * diagonalCost + std::abs(x - y) * cardinalCost;
		ll ans3 = std::min(x, y) * diagonalCost + (std::abs(x - y) >> 1) * (diagonalCost << 1) + (std::abs(x - y) & 1) * cardinalCost;
		std::cout << std::min({ans1, ans2, ans3}) << '\n';
	}
};

int main()
{
	fastio;
	Solver solver;
	solver.solve();
	return 0;
}