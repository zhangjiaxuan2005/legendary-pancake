//
// Created by 17246 on 2025/8/11.
//


#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {
    }

    explicit ListNode(int x) : val(x), next(nullptr) {
    }

    ListNode(int x, ListNode *next) : val(x), next(next) {
    }
};

ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
    if (list1 == nullptr) {
        return list2;
    }
    if (list2 == nullptr) {
        return list1;
    }
    if (list1->val < list2->val) {
        list1->next = mergeTwoLists(list1->next, list2);
        return list1;
    }
    list2->next = mergeTwoLists(list1, list2->next);
    return list2;
}

ListNode *mergeTwoLists2(ListNode *list1, ListNode *list2) {
    auto *preHead = new ListNode(-1);

    ListNode *prev = preHead;
    while (list1 != nullptr && list2 != nullptr) {
        if (list1->val < list2->val) {
            prev->next = list1;
            list1 = list1->next;
        } else {
            prev->next = list2;
            list2 = list2->next;
        }
        prev = prev->next;
    }
    prev->next = list1 == nullptr ? list2 : list1;

    return preHead->next;
}


int main() {
    auto *list1 = new ListNode(1);
    list1->next = new ListNode(2);
    list1->next->next = new ListNode(4);
    auto *list2 = new ListNode(1);
    list2->next = new ListNode(3);
    list2->next->next = new ListNode(4);
    ListNode *list = mergeTwoLists(list1, list2);
    while (list != nullptr) {
        cout << list->val << " ";
        list = list->next;
    }
    return 0;
}
