#include <vector>

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
    int find(int x)
    {
        return x == data[x] ? x : data[x] = find(data[x]);
    }
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if (x != y)
            x > y ? data[x] = y : data[y] = x;
    }
};