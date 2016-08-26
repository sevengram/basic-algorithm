#include "common.h"

struct node_compare
{
    bool operator()(const ListNode *x, const ListNode *y)
    {
        return x->val <= y->val;
    }
};

ListNode *mergeKLists(std::vector<ListNode *> &lists)
{
    priority_queue<ListNode *, vector<ListNode *>, node_compare> pq;
    for (ListNode *head: lists) {
        if (head) {
            pq.push(head);
        }
    }
    ListNode *result = nullptr;
    ListNode *p = nullptr;
    ListNode *q;
    while (!pq.empty()) {
        q = pq.top();
        if (p == nullptr) {
            result = new ListNode(q->val);
            p = result;
        } else {
            p->next = new ListNode(q->val);
            p = p->next;
        }
        pq.pop();
        if (q->next) {
            pq.push(q->next);
        }
    }
    return result;
}