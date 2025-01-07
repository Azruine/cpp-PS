#include <vector>
#include <iostream>
#include <deque>

using namespace std;

vector<int> solution(vector<int> arr) 
{
    std::deque<int> dq(arr.begin(), arr.end());
    int size = static_cast<int>(arr.size());
    for (int i = 0; i < size; i++)
    {
        int curTop = dq.front();
        dq.pop_front();
        if (curTop != dq.front() || i == size - 1)
            dq.push_back(curTop);
    }
    cout << "Hello Cpp" << endl;
    return std::vector<int>(dq.begin(), dq.end());
}