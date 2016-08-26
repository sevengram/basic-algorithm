//
// Created by jfan on 7/27/16.
//

#ifndef BASIC_COMMON_H
#define BASIC_COMMON_H

#include <vector>
#include <string>
#include <set>
#include <cmath>
#include <stack>
#include <list>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <queue>
#include <sstream>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) { }
};

struct ListNode
{
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) { }
};


int check_bit(int flag, int offset)
{
    return ((flag >> offset) & 0x1) != 0x0;
}

int set_bit(int flag, int offset)
{
    return flag | (1 << offset);
}

int clear_bit(int flag, int offset)
{
    return flag & ~(1 << offset);
}

unsigned int mask_range(int low, int hi)
{
    return (~0U << low) & (~0U >> (sizeof(int) * 8 - 1 - hi));
}

int reverse_part(int i, int low, int hi)
{
    return i ^ mask_range(low, hi);
}

#endif //BASIC_COMMON_H
