/*==== Copyright 2025 Azruine ====*/

#include <string>
#include <utility>
#include <vector>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

class UnionFind {
public:
    void init(size_t n) {
        this->n = n;
        data.resize(n);
        for (size_t i = 0; i < n; ++i) {
            data[i] = i;
        }
    }
    size_t find(size_t x) { return data[x] == x ? x : data[x] = find(data[x]); }
    void merge(size_t x, size_t y) {
        x = find(x), y = find(y);
        if (x != y) {
            x > y ? data[x] = y : data[y] = x;
        }
    }

private:
    size_t n{0};
    std::vector<size_t> data;
};

class Solution {
public:
    std::string smallestEquivalentString(std::string s1, std::string s2,
                                         std::string baseStr) {
        init();
        merge(s1, s2);
        return build(baseStr);
    }

private:
    UnionFind uf;
    constexpr static size_t ALPHABET_SIZE = 26;
    void init() { uf.init(ALPHABET_SIZE); }
    void merge(char chr1, char chr2) {
        uf.merge(as<size_t>(chr1 - 'a'), as<size_t>(chr2 - 'a'));
    }
    char find(char chr) {
        return as<char>(uf.find(as<size_t>(chr - 'a')) + 'a');
    }
    void merge(std::string const& s1, std::string const& s2) {
        for (size_t i = 0; i < s1.size(); ++i) {
            merge(s1[i], s2[i]);
        }
    }
    std::string build(std::string const& baseStr) {
        std::string res;
        res.reserve(baseStr.size());
        for (char chr : baseStr) {
            res.push_back(find(chr));
        }
        return res;
    }
};
