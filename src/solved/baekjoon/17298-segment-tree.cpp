#include <string>
#include <vector>
#include <climits>

using ll = long long int;
using ull = unsigned long long int;
using ld = long double;

#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

/////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Author : jinhan814
 * Date : 2021-05-06
 * Source : https://blog.naver.com/jinhan814/222266396476
 * Description : FastIO implementation for cin, cout. (mmap ver.)
 */
constexpr int SZ = 1 << 20;

class INPUT
{
private:
    char *p;
    bool __END_FLAG__, __GETLINE_FLAG__;

public:
    explicit operator bool() { return !__END_FLAG__; }
    INPUT()
    {
        struct stat st;
        fstat(0, &st);
        p = (char *)mmap(0, st.st_size, PROT_READ, MAP_SHARED, 0, 0);
    }
    bool IsBlank(char c) { return c == ' ' || c == '\n'; }
    bool IsEnd(char c) { return c == '\0'; }
    char _ReadChar() { return *p++; }
    char ReadChar()
    {
        char ret = _ReadChar();
        for (; IsBlank(ret); ret = _ReadChar())
            ;
        return ret;
    }
    template <typename T>
    T ReadInt()
    {
        T ret = 0;
        char cur = _ReadChar();
        bool flag = 0;
        for (; IsBlank(cur); cur = _ReadChar())
            ;
        if (cur == '-')
            flag = 1, cur = _ReadChar();
        for (; !IsBlank(cur) && !IsEnd(cur); cur = _ReadChar())
            ret = 10 * ret + (cur & 15);
        if (IsEnd(cur))
            __END_FLAG__ = 1;
        return flag ? -ret : ret;
    }
    std::string ReadString()
    {
        std::string ret;
        char cur = _ReadChar();
        for (; IsBlank(cur); cur = _ReadChar())
            ;
        for (; !IsBlank(cur) && !IsEnd(cur); cur = _ReadChar())
            ret.push_back(cur);
        if (IsEnd(cur))
            __END_FLAG__ = 1;
        return ret;
    }
    double ReadDouble()
    {
        std::string ret = ReadString();
        return stod(ret);
    }
    std::string getline()
    {
        std::string ret;
        char cur = _ReadChar();
        for (; cur != '\n' && !IsEnd(cur); cur = _ReadChar())
            ret.push_back(cur);
        if (__GETLINE_FLAG__)
            __END_FLAG__ = 1;
        if (IsEnd(cur))
            __GETLINE_FLAG__ = 1;
        return ret;
    }
    friend INPUT &getline(INPUT &in, std::string &s)
    {
        s = in.getline();
        return in;
    }
} _in;

class OUTPUT
{
private:
    char write_buf[SZ];
    int write_idx;

public:
    ~OUTPUT() { Flush(); }
    explicit operator bool() { return 1; }
    void Flush()
    {
        write(1, write_buf, write_idx);
        write_idx = 0;
    }
    void WriteChar(char c)
    {
        if (write_idx == SZ)
            Flush();
        write_buf[write_idx++] = c;
    }
    template <typename T>
    int GetSize(T n)
    {
        int ret = 1;
        for (n = n >= 0 ? n : -n; n >= 10; n /= 10)
            ret++;
        return ret;
    }
    template <typename T>
    void WriteInt(T n)
    {
        int sz = GetSize(n);
        if (write_idx + sz >= SZ)
            Flush();
        if (n < 0)
            write_buf[write_idx++] = '-', n = -n;
        for (int i = sz; i-- > 0; n /= 10)
            write_buf[write_idx + i] = n % 10 | 48;
        write_idx += sz;
    }
    void WriteString(std::string s)
    {
        for (auto &c : s)
            WriteChar(c);
    }
    void WriteDouble(double d) { WriteString(std::to_string(d)); }
} _out;

/* operators */
INPUT &operator>>(INPUT &in, char &i)
{
    i = in.ReadChar();
    return in;
}
INPUT &operator>>(INPUT &in, std::string &i)
{
    i = in.ReadString();
    return in;
}
template <typename T, typename std::enable_if_t<std::is_arithmetic_v<T>> * = nullptr>
INPUT &operator>>(INPUT &in, T &i)
{
    if constexpr (std::is_floating_point_v<T>)
        i = in.ReadDouble();
    else if constexpr (std::is_integral_v<T>)
        i = in.ReadInt<T>();
    return in;
}

OUTPUT &operator<<(OUTPUT &out, char i)
{
    out.WriteChar(i);
    return out;
}
OUTPUT &operator<<(OUTPUT &out, std::string i)
{
    out.WriteString(i);
    return out;
}
template <typename T, typename std::enable_if_t<std::is_arithmetic_v<T>> * = nullptr>
OUTPUT &operator<<(OUTPUT &out, T i)
{
    if constexpr (std::is_floating_point_v<T>)
        out.WriteDouble(i);
    else if constexpr (std::is_integral_v<T>)
        out.WriteInt<T>(i);
    return out;
}

/* macros */
#define cin _in
#define cout _out
#define istream INPUT
#define ostream OUTPUT
/////////////////////////////////////////////////////////////////////////////////////////////

class Seg
{
private:
    int size;
    std::vector<int> tree;
    void build()
    {
        for (int i = size - 1; i > 0; i--)
            tree[i] = std::max(tree[i << 1], tree[i << 1 | 1]);
    }

public:
    Seg() {}
    ~Seg() {}
    void setSize(int n)
    {
        size = n;
    }
    void init()
    {
        tree.resize(size << 1);
        for (int i = size; i < size << 1; i++)
            cin >> tree[i];
        build();
    }
    /**
     * @brief get the value of idx
     * @param idx index
     */
    int getValue(int idx)
    {
        return tree[size + idx];
    }
    /**
     * @brief query the maximum value in range [l, r)
     * @param l left index
     * @param r right index
     */
    int query(int l, int r)
    {
        if (l >= r)
            return INT_MIN;
        if (l == r - 1)
            return tree[l + size];
        int ret = INT_MIN;
        for (l += size, r += size; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                ret = std::max(ret, tree[l++]);
            if (r & 1)
                ret = std::max(ret, tree[--r]);
        }
        return ret;
    }
    /**
     * @brief find leftmost index where the value is greater than or equal to val using binary search
     * @param l left index
     * @param r right index
     * @param val value
     */
    int findLeftmost(int l, int r, int val)
    {
        int l0 = l;
        while (l < r)
        {
            int mid = (l + r) >> 1;
            if (query(l0, mid + 1) > val)
                r = mid;
            else
                l = mid + 1;
        }
        return l;
    }
};

class Solver
{
private:
    int n;
    Seg seg;

public:
    Solver()
    {
        cin >> n;
        seg.setSize(n);
        seg.init();
    }
    ~Solver() {}
    void solve()
    {
        for (int i = 0; i < n; i++)
        {
            int val = seg.getValue(i);
            int idx = seg.findLeftmost(i + 1, n, val);
            if (idx == n && seg.getValue(n - 1) <= val)
                cout << "-1 ";
            else
                cout << seg.getValue(idx) << ' ';
        }
    }
};

int main()
{
    Solver solver;
    solver.solve();
    return 0;
}