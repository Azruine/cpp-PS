/*==== Copyright 2025 Azruine ====*/

#include <cstdint>
#include <queue>
#include <utility>
#include <vector>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

class Solution {
public:
    int32_t maxCandies(std::vector<int32_t>& status,
                       std::vector<int32_t>& candies,
                       std::vector<std::vector<int32_t>>& keys,
                       std::vector<std::vector<int32_t>>& containedBoxes,
                       std::vector<int32_t>& initialBoxes) {
        std::queue<size_t> queue;
        // 열 수 있는 박스인가?
        std::vector<bool> boxUnlocked(status.size(), false);
        // 얻은 박스인가?
        std::vector<bool> boxObtained(status.size(), false);
        // 이미 사용한 박스인가?
        std::vector<bool> boxUsed(status.size(), false);
        int32_t ret{0};
        for (auto& box : initialBoxes) {
            queue.push(as<size_t>(box));
            boxObtained[as<size_t>(box)] = true;
            if (status[as<size_t>(box)] == 1) {
                boxUnlocked[as<size_t>(box)] = true;
            }
        }
        while (!queue.empty()) {
            auto box = queue.front();
            queue.pop();
            if (boxUsed[box] || !boxUnlocked[box] || !boxObtained[box]) {
                continue;
            }
            boxUsed[box] = true;
            ret += candies[box];
            for (auto& key : keys[box]) {
                if (!boxUnlocked[as<size_t>(key)]) {
                    boxUnlocked[as<size_t>(key)] = true;
                    if (boxObtained[as<size_t>(key)]) {
                        queue.push(as<size_t>(key));
                    }
                }
            }

            for (auto& containedBox : containedBoxes[box]) {
                if (!boxObtained[as<size_t>(containedBox)]) {
                    boxObtained[as<size_t>(containedBox)] = true;
                    if (status[as<size_t>(containedBox)] == 1) {
                        boxUnlocked[as<size_t>(containedBox)] = true;
                    }
                    queue.push(as<size_t>(containedBox));
                }
            }
        }
        return ret;
    }
};
