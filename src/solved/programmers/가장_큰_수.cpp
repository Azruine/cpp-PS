#include <string>
#include <vector>
#include <algorithm>

using namespace std;
string solution(vector<int> numbers) {
    string answer = "";
    std::vector<std::string> v;
    std::for_each(numbers.begin(), numbers.end(), [&](const int &x){v.emplace_back(std::to_string(x));});
    std::sort(v.begin(), v.end(), [](const std::string &lhs, const std::string &rhs){return lhs + rhs > rhs + lhs;});
    std::for_each(v.begin(), v.end(), [&](const std::string s){answer += s;});
    return answer[0] != '0' ? answer : "0";
}