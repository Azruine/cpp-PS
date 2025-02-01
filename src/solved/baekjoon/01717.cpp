#include <iostream>
#include <vector>
#include <unordered_set>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                         \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class UnionFind
{
private:
    std::vector<int> data;

public:
    UnionFind() {}
    ~UnionFind() {}
    void init(int n)
    {
        data.resize(n);
        for (int i = 0; i < n; i++)
            data[i] = i;
    }
    int find(int a)
    {
        if (data[a] == a)
            return a;
        data[a] = find(data[a]);
        return data[a];
    }
    void union_(int a, int b)
    {
        a = find(a), b = find(b);
        if (a != b)
        {
            if (a > b)
                std::swap(a, b);
            data[b] = a;
        }
        return;
    }
};

class Solver
{
private:
    int n, m;
    UnionFind uf;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> n >> m;
        uf.init(n + 1);
        int query, a, b;
        while (std::cin >> query >> a >> b)
        {
            if (query == 0)
                uf.union_(a, b);
            else if (query == 1)
                std::cout << (uf.find(a) == uf.find(b) ? "YES\n" : "NO\n");
        }
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}