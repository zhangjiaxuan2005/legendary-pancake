//
// Created by 17246 on 2025/8/3.
// LeetCode 160
//

#include <iostream>
#include <memory>
#include <unordered_set>

using namespace std;

struct ListNode
{
    int val;
    ListNode* next;

    explicit ListNode(int x) : val(x), next(nullptr)
    {
    }
};

ListNode* getIntersectionNode(ListNode* headA, ListNode* headB)
{
    if (headA == nullptr || headB == nullptr)
    {
        return nullptr;
    }
    ListNode* pA = headA;
    ListNode* pB = headB;
    while (pA != pB)
    {
        pA = pA == nullptr ? headB : pA->next;
        pB = pB == nullptr ? headA : pB->next;
    }
    return pA;
}

ListNode* getIntersectionNode2(ListNode* headA, ListNode* headB)
{
    unordered_set<ListNode *> visited;
    ListNode *temp = headA;
    while (temp != nullptr) {
        visited.insert(temp);
        temp = temp->next;
    }
    temp = headB;
    while (temp != nullptr) {
        if (visited.contains(temp)) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;

}


int main()
{
    unique_ptr<ListNode> headA(new ListNode(4));
    headA->next = new ListNode(1);
    headA->next->next = new ListNode(8);
    headA->next->next->next = new ListNode(4);
    headA->next->next->next->next = new ListNode(5);

    unique_ptr<ListNode> headB(new ListNode(5));
    headB->next = new ListNode(6);
    headB->next->next = new ListNode(1);
    headB->next->next->next = headA->next->next;

    ListNode* intersection_node = getIntersectionNode(headA.get(), headB.get());
    if (intersection_node)
    {
        cout << intersection_node->val << endl;
    }
    else
    {
        cout << "No intersection" << endl;
    }
}
