#include <vector>
#include <unordered_set>
#include <algorithm>

int solution(std::vector<int> nums)
{
    int answer = 0;
    std::unordered_set<int> s(nums.begin(), nums.end());
    answer = std::min(static_cast<int>(nums.size()) >> 1, static_cast<int>(s.size()));
    return answer;
}