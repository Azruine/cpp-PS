#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

bool solution(vector<string> phone_book) {
    std::unordered_set<std::string> s;
    std::for_each(phone_book.begin(), phone_book.end(), [&s](const std::string &num){
        int len = num.length();
        for (int i = 0; i < len; i++)
            s.insert(num.substr(0, i));
        return;
    });
    return std::find_if(phone_book.begin(), phone_book.end(), [&s](const std::string &num){
        return s.find(num) != s.end();
    }) == phone_book.end();
}