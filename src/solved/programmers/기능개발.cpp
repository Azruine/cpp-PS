#include <vector>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    int n = static_cast<int>(speeds.size());
    int day = 0;
    for (int i = 0; i < n;)
    {
        int temp = 0;
        day += (100 - progresses[i] + (speeds[i] - 1)) / speeds[i];
        progresses[i] += day * speeds[i];
        while (progresses[i] >= 100)
        {
            i++;
            temp++;
            if (i >= n)
                break;
            progresses[i] += speeds[i] * day;
        }
        answer.push_back(temp);
    }
    return answer;
}