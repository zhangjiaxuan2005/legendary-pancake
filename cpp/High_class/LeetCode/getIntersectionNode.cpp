//
// Created by 17246 on 2025/8/3.
// LeetCode 160
//

#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    if (headA == nullptr || headB == nullptr) {
        return nullptr;
    }
    ListNode *pA = headA;
    ListNode *pB = headB;
    while (pA != pB) {
        pA = pA == nullptr ? headB : pA->next;
        pB = pB == nullptr ? headA : pB->next;
    }
    return pA;
}

int main()
{
    vector<int> listA={4,1,8,4,5};
    vector<int> listB={5,6,1,8,4,5};
    ListNode *headA = new ListNode(listA[0]);
    ListNode *headB = new ListNode(listB[0]);
    ListNode *pA = headA;
    ListNode *pB = headB;
    for (int i = 1; i < listA.size(); i++) {
        pA->next = new ListNode(listA[i]);
        pA = pA->next;
    }
    for (int i = 1; i < listB.size(); i++) {
        pB->next = new ListNode(listB[i]);
        pB = pB->next;
    }
    ListNode *intersectionNode = getIntersectionNode(headA, headB);
    if (intersectionNode) {
        cout << intersectionNode->val << endl;
    } else
    {
        cout << "No intersection" << endl;
    }
    while (headA) {
        ListNode *temp = headA;
        headA = headA->next;
        delete temp;
    }
    while (headB) {
        ListNode *temp = headB;
        headB = headB->next;
        delete temp;
    }
}
