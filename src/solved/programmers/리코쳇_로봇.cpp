#include <string>
#include <vector>
#include <queue>
#include <array>

using namespace std;

std::array<std::pair<int, int>, 4> dirs = {{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}};

bool valid(std::vector<std::string> &board, int i, int j)
{
    int row = static_cast<int>(board.size());
    int col = board[0].length();
    if (i >= 0 && i < row && j >= 0 && j < col && board[i][j] != 'D')
        return true;
    return false;
}

int bfs(std::vector<std::string> &board)
{
    std::queue<std::pair<int, int>> q;
    int row = static_cast<int>(board.size());
    int col = board[0].length();
    std::vector<std::vector<int>> distance(row, std::vector<int>(col, -1));
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (board[i][j] == 'R')
            {
                q.push({i, j});
                distance[i][j] = 0;
            }
                
    while (!q.empty())
    {
        auto [i, j] = q.front();
        q.pop();
        for (auto dir : dirs)
        {
            int ni = i, nj = j;
            while (valid(board, ni + dir.first, nj + dir.second))
            {
                ni += dir.first;
                nj += dir.second;
            }
            if (distance[ni][nj] == -1)
            {
                q.push({ni, nj});
                distance[ni][nj] = distance[i][j] + 1;
            }
                
        }
    }
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (board[i][j] == 'G')
                return distance[i][j];
}

int solution(vector<string> board) {
    int answer = 0;
    return bfs(board);
}