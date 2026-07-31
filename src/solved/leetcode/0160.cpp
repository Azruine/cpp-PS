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
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        int32_t len_a = 0;
        int32_t len_b = 0;
        ListNode* new_a = headA;
        ListNode* new_b = headB;
        while (new_a != nullptr) {
            len_a += 1;
            new_a = new_a->next;
        }
        while (new_b != nullptr) {
            len_b += 1;
            new_b = new_b->next;
        }
        if (len_a < len_b) {
            std::swap(headA, headB);
            std::swap(len_a, len_b);
        }
        int32_t diff = len_a - len_b;
        while (diff--) {
            headA = headA->next;
        }
        while (headA != nullptr && headA != headB) {
            headA = headA->next;
            headB = headB->next;
        }
        return headA;
    }
};
