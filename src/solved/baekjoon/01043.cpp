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
    std::unordered_set<int> truth;
    std::vector<std::vector<int>> party;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> n >> m;
        int temp, man;
        std::cin >> temp;
        while (temp--)
        {
            std::cin >> man;
            truth.insert(man - 1);
        }

        UnionFind uf;
        uf.init(n);
        party.resize(m);
        for (int i = 0; i < m; i++)
        {
            std::cin >> man;
            while (man--)
            {
                std::cin >> temp;
                party[i].push_back(temp);
            }
        }
        for (auto &p : party)
        {
            int a = p.front();
            for (int i = 1; i < static_cast<int>(p.size()); i++)
                uf.union_(a - 1, p[i] - 1);
        }
        std::unordered_set<int> newTruth;
        for (auto &i : truth)
            newTruth.insert(uf.find(i));
        
        int ans = 0;
        for (auto &p : party)
        {
            if (!newTruth.contains(uf.find(p.front() - 1)))
                ans++;
        }
        std::cout << ans;
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}