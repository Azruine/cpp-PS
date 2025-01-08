#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
struct comp
{
    bool operator()(const std::pair<int, int> &lhs, const std::pair<int, int> &rhs)
    {
        if (lhs.first == rhs.first)
        {
            return lhs.second > rhs.second;
        }
        return lhs.first < rhs.first;
    }
};

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    int n = static_cast<int>(plays.size());
    std::unordered_map<std::string, int> m;
    std::unordered_map<std::string, std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, comp>> musicData;
    for (int i = 0; i < n; i++)
    {
        m[genres[i]] += plays[i];
        musicData[genres[i]].push({plays[i], i});
    }
    std::vector<std::pair<int, std::string>> tot;
    for (auto &music : m)
    {
        tot.push_back({music.second, music.first});
    }
    std::sort(tot.begin(), tot.end(), [&](const std::pair<int, std::string> &lhs, const std::pair<int, std::string> &rhs){return lhs.first > rhs.first;});
    for (auto &music : tot)
    {
        answer.push_back(musicData[music.second].top().second);
        musicData[music.second].pop();
        if (musicData[music.second].empty())
            continue;
        answer.push_back(musicData[music.second].top().second);
    }
    return answer;
}