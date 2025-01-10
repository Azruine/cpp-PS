#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using ll = long long int;

using namespace std; // what 

int solution(vector<int> scoville, int K) {
    int answer = 0;
    std::priority_queue<ll, std::vector<ll>, std::greater<ll>> pq(scoville.begin(), scoville.end());
    ll x, y;
    int cnt = 0;
    while (pq.size() > 1)
    {
        x = pq.top();
        pq.pop();
        if (x >= K)
            break;
        cnt++;
        y = pq.top();
        pq.pop();
        ll temp = x + y * 2;
        pq.push(temp);
    }
    return (pq.empty() || pq.top() < K) ? -1 : cnt;
}