//
// Created by 17246 on 2025/8/4.
//

#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode* next;

    ListNode() : val(0), next(nullptr)
    {
    }

    ListNode(int x) : val(x), next(nullptr)
    {
    }

    ListNode(int x, ListNode* next) : val(x), next(next)
    {
    }
};

ListNode* reverseList(ListNode* head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return head;
    }
    ListNode* prev = nullptr;
    ListNode* curr = head;
    while (curr != nullptr)
    {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

int main()
{
    auto* head =new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    ListNode* newHead = reverseList(head);
    while (newHead != nullptr)
    {
        cout << newHead->val << endl;
        newHead = newHead->next;
    }
    while (head != nullptr)
    {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
    return 0;
}
