#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> triangle) {
    auto data = triangle;
    for (int i = 1; i < static_cast<int>(data.size()); i++)
    {
        for (int j = 0; j < static_cast<int>(data[i].size()); j++)
        {
            if (j == 0)
                data[i][j] = data[i - 1][j] + triangle[i][j];
            else if (j == static_cast<int>(data[i].size()) - 1)
                data[i][j] = data[i - 1][j - 1] + triangle[i][j];
            else
                data[i][j] = std::max(data[i - 1][j] + triangle[i][j], std::max(data[i - 1][j - 1] + triangle[i][j], data[i][j]));
        }
    }
    int answer = *std::max_element(data.back().begin(), data.back().end());
    return answer;
}