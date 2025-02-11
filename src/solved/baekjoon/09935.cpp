#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#define 고속입출력                           \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);                    \
    std::cout.tie(NULL);

class Solver
{
private:
    std::string target, explode;
    std::vector<char> st;
    std::vector<char> temp;

public:
    Solver() {}
    ~Solver() {}
    void solve()
    {
        std::cin >> target >> explode;
        int n = static_cast<int>(target.length());
        int m = static_cast<int>(explode.length());
        for (int i = 0; i < n; i++)
        {
            char c = target[i];
            bool explosive = false;
            if (c != explode.back())
            {
                st.push_back(c);
            }
            else
            {
                temp.push_back(c);
                explosive = true;
                for (int j = m - 2; j >= 0; j--)
                {
                    if (st.empty())
                    {
                        explosive = false;
                        break;
                    }
                    char cur = st.back();
                    st.pop_back();
                    temp.push_back(cur);
                    if (cur != explode[j])
                    {
                        explosive = false;
                        break;
                    }
                }
                if (explosive)
                    temp = std::vector<char>();
                else
                {
                    while(!temp.empty())
                    {
                        st.push_back(temp.back());
                        temp.pop_back();
                    }
                }
            }
        }
        if (st.empty())
            std::print("FRULA");
        else
            for (auto &c : st)
                std::print("{}", c);
    }
};

int main()
{
    고속입출력;
    Solver solver;
    solver.solve();
    return 0;
}