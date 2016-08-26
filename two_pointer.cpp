#include "common.h"

// 11. Container With Most Water
int maxArea(vector<int> &height)
{
    int l = 0;
    int r = height.size() - 1;
    int minHeight = 0;
    int maxArea = 0;
    while (l < r) {
        if (height[l] <= minHeight) {
            l++;
        } else if (height[r] <= minHeight) {
            r--;
        } else {
            minHeight = height[l] < height[r] ? height[l++] : height[r--];
            maxArea = max(maxArea, (r - l + 1) * minHeight);
        }
    }
    return maxArea;
}

// Trapping Rain Water
int trap(vector<int> &height)
{
    int l = 0;
    int r = height.size() - 1;
    int sum = 0;
    int level = 0;
    while (l < r) {
        if (height[l] < height[r]) {
            level = max(height[l], level);
            sum += level - height[l];
            l++;
        } else {
            level = max(height[r], level);
            sum += level - height[r];
            r--;
        }
    }
    return sum;
}