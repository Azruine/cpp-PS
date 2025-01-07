#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    std::unordered_map<std::string, int> m;
    for (auto &p : participant)
        m[p]++;
    for (auto &c : completion)
        m[c]--;
    for (auto &p : participant)
        if (m[p] != 0)
            return p;
}