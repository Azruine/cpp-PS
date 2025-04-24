/*==== Copyright 2025 Azruine ====*/

#include <cstdint>
#include <utility>

namespace {
template <typename To, typename From>
constexpr To as(From&& from) {
    return static_cast<To>(std::forward<From>(from));
}
}  // namespace

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next_) : val(x), next(next_) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int32_t carry{0};
        int32_t cur_digit{0};
        static constexpr int32_t base{10};
        auto ret = ListNode{0};
        ListNode* next = nullptr;

        for (ListNode* cur = &ret; l1 || l2 || carry > 0; cur = cur->next) {
            cur_digit = carry;
            if (l1) {
                cur_digit += l1->val;
                l1 = l1->next;
            }
            if (l2) {
                cur_digit += l2->val;
                l2 = l2->next;
            }
            carry = cur_digit / base;
            cur_digit %= base;
            next = new ListNode(cur_digit);
            cur->next = next;
        }
        return ret.next;
    }
};
