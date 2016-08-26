#include "common.h"

string addBinary(string a, string b)
{
    int m = a.size();
    int n = b.size();
    int bit_a;
    int bit_b;
    int bit_c = 0;
    int sum;
    string result;
    for (int i = 0; i < max(m, n); i++) {
        bit_a = (i < m) ? (a[m - 1 - i] - '0') : 0;
        bit_b = (i < n) ? (b[n - 1 - i] - '0') : 0;
        sum = bit_a + bit_b + bit_c;
        result = (char) ('0' + (sum % 2)) + result;
        bit_c = sum / 2;
    }
    if (bit_c != 0) {
        result = '1' + result;
    }
    return result;
}

vector<int> addNumbers(const vector<int> &a, const vector<int> &b)
{
    int m = a.size();
    int n = b.size();
    int num_a, num_b, sum;
    int num_c = 0;
    vector<int> result;
    for (int i = 0; i < max(m, n); i++) {
        num_a = (i < m) ? a[m - 1 - i] : 0;
        num_b = (i < n) ? a[n - 1 - i] : 0;
        sum = num_a + num_b + num_c;
        result.push_back(sum % 10);
        num_c = sum / 10;
    }
    if (num_c != 0) {
        result.push_back(num_c);
    }
    reverse(result.begin(), result.end());
    return result;
}

ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
{
    int v1, v2;
    int v3 = 0;
    int sum;
    ListNode *result = nullptr;
    ListNode *p = nullptr;
    while (l1 || l2) {
        v1 = l1 ? l1->val : 0;
        v2 = l2 ? l2->val : 0;
        sum = v1 + v2 + v3;
        l1 = l1 ? l1->next : nullptr;
        l2 = l2 ? l2->next : nullptr;
        if (p == nullptr) {
            p = new ListNode(sum % 10);
            result = p;
        } else {
            if (sum != 0 || l1 || l2) {
                p->next = new ListNode(sum % 10);
                p = p->next;
            }
        }
        v3 = sum / 10;
    }
    if (v3 != 0 && p) {
        p->next = new ListNode(v3);
    }
    return result;
}

vector<int> plusOne(vector<int> &digits)
{
    std::vector<int> result(digits.size(), 0);
    int overflow = 1;
    for (int i = digits.size() - 1; i >= 0; i--) {
        int s = digits[i] + overflow;
        result[i] = s % 10;
        overflow = s / 10;
    }
    if (overflow != 0) {
        result.insert(result.begin(), overflow);
    }
    return result;
}