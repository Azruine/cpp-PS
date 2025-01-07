#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int solution(vector<vector<string>> clothes) {
    int answer = 1;
    std::unordered_map<std::string, int> m;
    for (auto &cPair : clothes)
    {
        m[cPair[1]]++;
    }
    for (auto it = m.begin(); it != m.end(); it++)
    {
        answer *= it->second + 1;
    }
    return answer - 1;
}