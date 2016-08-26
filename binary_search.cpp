#include "common.h"

int binary_search(std::vector<int> v, int target)
{
    int left = 0;
    int right = v.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (target < v[mid]) {
            right = mid - 1;
        } else if (target > v[mid]) {
            left = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

int search_in_rotated(std::vector<int> &v, int target)
{
    int left = 0;
    int right = v.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (target == v[mid]) {
            return mid;
        }
        if (v[left] < v[mid]) {
            if (v[left] <= target && target < v[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else if (v[left] > v[mid]) {
            if (v[mid] < target && target <= v[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        } else {
            left++;
        }
    }
    return -1;
}

int find_min_in_rotated(std::vector<int> v)
{
    int left = 0;
    int right = v.size() - 1;
    while (left < right && v[left] >= v[right]) {
        int mid = (left + right) / 2;
        if (v[left] < v[mid]) {
            left = mid + 1;
        } else if (v[left] > v[mid]) {
            right = mid;
        } else {
            left++;
        }
    }
    return v[left];
}

int insert_index(std::vector<int> v, int num)
{
    int left = 0;
    int right = v.size();
    while (left < right) {
        int mid = (left + right) / 2;
        if (num < v[mid]) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return right;
}

vector<int> searchRange(vector<int> &nums, int target)
{
    int l = 0;
    int r = nums.size() - 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (target < nums[mid]) {
            r = mid - 1;
        } else if (target > nums[mid]) {
            l = mid + 1;
        } else {
            int lb = mid;
            int rb = mid;
            while (nums[lb - 1] == target && lb - 1 >= l) {
                lb--;
            }
            while (nums[rb + 1] == target && rb + 1 <= r) {
                rb++;
            }
            return {lb, rb};
        }
    }
    return {-1, -1};
}

int main()
{
    vector<int> v = {1, 3, 6, 6, 10, 15};
    cout << insert_index(v, 0) << endl;
    cout << insert_index(v, 1) << endl;
    cout << insert_index(v, 2) << endl;
    cout << insert_index(v, 4) << endl;
    cout << insert_index(v, 6) << endl;
    cout << insert_index(v, 12) << endl;
    cout << insert_index(v, 15) << endl;
    cout << insert_index(v, 25) << endl;
    return 0;
}
