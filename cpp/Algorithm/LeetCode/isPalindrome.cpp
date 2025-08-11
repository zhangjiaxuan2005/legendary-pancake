//
// Created by 17246 on 2025/8/6.
// LeetCode 234
//

#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;

    ListNode() : val(0), next(nullptr) {
    }

    explicit ListNode(int x) : val(x), next(nullptr) {
    }

    ListNode(int x, ListNode* next) : val(x), next(next) {
    }
};

ListNode* reverse(ListNode* slow, ListNode* fast) {
    ListNode* pre = nullptr;
    ListNode* cur = slow;
    while (cur != fast) {
        ListNode* next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    return pre;
}


bool isPalindrome(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return true;
    }
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    if (fast != nullptr) {
        slow = slow->next;
    }
    slow = reverse(slow, nullptr);
    fast = head;
    while (slow != nullptr) {
        if (fast->val != slow->val) {
            return false;
        }
        fast = fast->next;
        slow = slow->next;
    }
    return true;
}
bool isPalindrome2(ListNode* head) {
    vector<int> vec;
    while (head != nullptr) {
        vec.push_back(head->val);
        head = head->next;
    }
    int left = 0;
    int right = vec.size() - 1;
    while (left < right) {
        if (vec[left] != vec[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

int main() {
    auto * head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(2);
    head->next->next->next = new ListNode(1);
    bool res = isPalindrome(head);
    cout << res << endl;
    while (head != nullptr) {
        ListNode * next = head->next;
        delete head;
        head = next;
    }
    return 0;

}
