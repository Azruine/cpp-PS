/*==== Copyright 2025 Azruine ====*/

#include <array>
#include <cstdint>
#include <iterator>
#include <unordered_set>
#include <utility>
#include <vector>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

class Twitter {
private:
    static constexpr size_t MAX{510};
    static constexpr size_t MAX_NEWS{10};
    std::array<std::unordered_set<int32_t>, MAX> users;
    std::vector<std::pair<int32_t, int32_t>> tweets;

public:
    void postTweet(int userId, int tweetId) {
        tweets.emplace_back(userId, tweetId);
    }

    std::vector<int> getNewsFeed(int userId) {
        std::vector<int32_t> news;
        size_t cnt{0};
        auto it = tweets.end();
        while (cnt < MAX_NEWS && it != tweets.begin()) {
            std::advance(it, -1);
            auto& [user, tweet] = *it;
            if (user == userId || users.at(as<size_t>(userId)).contains(user)) {
                news.push_back(tweet);
                cnt++;
            }
        }
        return news;
    }

    void follow(int followerId, int followeeId) {
        users.at(as<size_t>(followerId)).insert(followeeId);
    }

    void unfollow(int followerId, int followeeId) {
        users.at(as<size_t>(followerId)).erase(followeeId);
    }
};
