//
// Created by 17246 on 2025/8/7.
// LeetCode 141
//

#include <unordered_set>
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;

    explicit ListNode(int x) : val(x), next(nullptr) {
    }
};

bool hasCycle(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return false;
    }
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}

bool hasCycle2(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return false;
    }
    unordered_set<ListNode*> seen;
    while (head != nullptr) {
        if (seen.count(head)) {
            return true;
        }
        seen.insert(head);
        head = head->next;
    }
    return false;
}


int main() {
    auto head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = head;
    cout << hasCycle(head) << endl;
    while (head != nullptr) {
        const auto temp = head;
        head = head->next;
        delete temp;
    }
    return 0;
}
