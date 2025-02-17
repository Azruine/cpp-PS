#include <bits/stdc++.h>

class Solution
{
private:
    int tot = 0;

public:
    void back(std::string &tiles, std::string path, std::vector<bool> &used)
    {
        if (path.length() > 0)
            tot++;
        for (int i = 0; i < tiles.length(); i++)
        {
            if (used[i])
                continue;
            if (i > 0 && tiles[i] == tiles[i - 1] && !used[i - 1])
                continue;
            used[i] = true;
            back(tiles, path + tiles[i], used);
            used[i] = false;
        }
    }
    int numTilePossibilities(std::string tiles)
    {
        std::sort(tiles.begin(), tiles.end());
        std::cout << tiles;
        std::vector<bool> used(tiles.length(), false);
        back(tiles, "", used);
        return tot;
    }
};