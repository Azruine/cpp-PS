/*==== Copyright 2025 Azruine ====*/

#include <ranges>
#include <utility>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
struct Range {
    template <typename Sentinel>
    constexpr auto operator()(Sentinel sentinel) const noexcept {
        return std::views::iota(static_cast<Sentinel>(0), sentinel);
    }
    template <typename Start, typename Sentinel>
    constexpr auto operator()(Start start, Sentinel sentinel) const noexcept {
        return std::views::iota(start, sentinel);
    }
    template <typename Start, typename Sentinel, typename Step>
    constexpr auto operator()(Start start, Sentinel sentinel,
                              Step step) const noexcept {
        return std::views::iota(start, sentinel) | std::views::stride(step);
    }
};
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
constexpr Range _iota{};
#pragma GCC diagnostic pop
}  // namespace

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0, head);
        ListNode* group_prev = &dummy;
        while (group_prev->next != nullptr) {
            ListNode* group_end = group_prev;
            for (int32_t i = 0; i < k; i++) {
                group_end = group_end->next;
                if (group_end == nullptr) {
                    break;
                }
            }
            ListNode* group_next = group_end->next;
            ListNode* old_head = group_prev->next;

            ListNode* prev = group_next;
            ListNode* cur = group_prev->next;

            while (cur != group_next) {
                ListNode* next = cur->next;
                cur->next = prev;
                prev = cur;
                cur = next;
            }

            group_prev->next = group_end;
            group_prev = old_head;
        }
        return dummy.next;
    }
};
