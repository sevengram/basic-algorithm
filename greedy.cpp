#include "common.h"

bool canJump2(vector<int> &nums)
{
    int n = nums.size();
    if (n == 0) {
        return false;
    }
    // 记录历史跳最远距离
    int distance = 0;
    for (int i = 0; i < n && i <= distance; i++) {
        // nums[i]+i当前跳最远距离 distance为i之前跳最远距离
        distance = max(nums[i] + i, distance);
    }
    if (distance < n - 1) {
        return false;
    }
    return true;
}

int jump2(vector<int> &nums)
{
    if (nums.size() == 0) {
        return -1;
    }
    if (nums.size() == 1) {
        return 0;
    }
    int start = 0;
    int end = 0;
    int count = 0;
    int farthest = 0;
    while (end < nums.size() - 1) {
        count++;
        for (int i = start; i <= end; i++) {
            farthest = max(farthest, i + nums[i]);
        }
        start = end + 1;
        end = farthest;
    }
    return count;
}