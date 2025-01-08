#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> citations) {
    int answer = 0;
    std::sort(citations.begin(), citations.end());
    int n = static_cast<int>(citations.size());
    for (int h = 0; h <= 10000; h++)
    {
        int idx = std::lower_bound(citations.begin(), citations.end(), h) - citations.begin();
        if (n - idx >= h)
            answer = h;
    }
    return answer;
}