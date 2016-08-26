#include "common.h"

list_node *reverse(list_node *head, list_node *end)
{
    if (head == nullptr || end == nullptr) {
        return nullptr;
    }
    if (head == end || head->next == nullptr) {
        return head;
    }
    list_node *p = head;
    list_node *q = p->next;
    do {
        list_node *old_next = q->next;
        q->next = p;
        p = q;
        q = old_next;
    } while (p != end && q != nullptr);
    return end;
}

int component_count(vector<list_node *> l)
{
    unordered_map<list_node *, bool> nodes_map;
    for (auto n : l) {
        nodes_map[n] = false;
    }
    int count = 0;
    for (auto kv: nodes_map) {
        if (kv.second) {
            continue;
        }
        count++;
        kv.second = true;
        list_node *n = (kv.first)->next;
        while (n != nullptr) {
            if (nodes_map.find(n) == nodes_map.end()) {
                break;
            } else {
                nodes_map[n] = true;
                n = n->next;
            }
        }
        n = (kv.first)->prev;
        while (n != nullptr) {
            if (nodes_map.find(n) == nodes_map.end()) {
                break;
            } else {
                nodes_map[n] = true;
                n = n->prev;
            }
        }
    }
    return count;
}