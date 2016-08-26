#include "common.h"

std::vector<int> twoSum(std::vector<int> &nums, int target)
{
    std::unordered_map<int, int> m;
    for (int i = 0; i < nums.size(); i++) {
        int remain = target - nums[i];
        if (m.find(remain) != m.end()) {
            return {m[remain], i};
        } else {
            m[nums[i]] = i;
        }
    }
    return {};
}

vector<vector<int>> two_sum(vector<int> &nums, int target)
{
    sort(nums.begin(), nums.end());
    int i = 0;
    int j = nums.size() - 1;
    vector<vector<int>> result;
    while (i < j) {
        if (nums[i] + nums[j] > target) {
            j--;
        } else if (nums[i] + nums[j] < target) {
            i++;
        } else {
            result.push_back({nums[i], nums[j]});
            i++;
            j--;
        }
    }
    return result;
}

vector<vector<int>> two_sum_less(vector<int> &nums, int target)
{
    sort(nums.begin(), nums.end());
    int i = 0;
    int j = nums.size() - 1;
    vector<vector<int>> result;
    while (i < j) {
        if (nums[i] + nums[j] <= target) {
            result.push_back({nums[i], nums[j]});
            for (int k = j - 1; k > i; k--) {
                result.push_back({nums[i], nums[k]});
            }
            i++;
        } else {
            j--;
        }
    }
    return result;
}


vector<vector<int>> three_sum(vector<int> &nums, int target)
{
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    int n = nums.size();
    for (int i = 0; i < n - 2; i++) {
        int j = i + 1;
        int k = n - 1;
        while (j < k) {
            if (nums[i] + nums[j] + nums[k] > target) {
                k--;
            } else if (nums[i] + nums[j] + nums[k] < target) {
                j++;
            } else {
                result.push_back(vector<int>({nums[i], nums[j], nums[k]}));
                j++;
                k--;
            }
        }
    }
    return result;
}

vector<vector<int>> three_sum_less(vector<int> &nums, int target)
{
    std::sort(nums.begin(), nums.end());
    int first, second, third;
    int remain;
    int n = nums.size();
    vector<vector<int>> result;
    for (int i = 0; i < n - 2; i++) {
        first = nums[i];
        remain = target - first;
        int j = i + 1;
        int k = n - 1;
        while (j < k) {
            second = nums[j];
            third = nums[k];
            if (second + third <= remain) {
                result.push_back({first, second, third});
                for (int l = k - 1; l > j; l--) {
                    result.push_back({first, second, nums[l]});
                }
                j++;
            } else {
                k--;
            }
        }
    }
    return result;
}


vector<vector<int>> four_sum(vector<int> &nums, int target)
{
    vector<vector<int>> result;
    int n = nums.size();
    sort(nums.begin(), nums.end());
    for (int i = 0; i < n - 3; i++) {
        for (int j = n - 1; j >= i + 3; j--) {
            int p = i + 1;
            int q = j - 1;
            int remain = target - nums[i] - nums[j];
            while (p < q) {
                if (nums[p] + nums[q] > remain) {
                    q--;
                } else if (nums[p] + nums[q] < remain) {
                    p++;
                } else {
                    result.push_back(std::vector<int>({nums[i], nums[p], nums[q], nums[j]}));
                    p++;
                    q--;
                }
            }
        }
    }
    return result;
}

void rec_k_sum(vector<int> &nums, int left, int target, int k, vector<int> &temp, vector<vector<int>> &result)
{
    if (k == 2) {
        int i = left;
        int j = nums.size() - 1;
        while (i < j) {
            if (nums[i] + nums[j] > target) {
                j--;
            } else if (nums[i] + nums[j] < target) {
                i++;
            } else {
                vector<int> dup = temp;
                dup.push_back(nums[i]);
                dup.push_back(nums[j]);
                result.push_back(dup);
                i++;
                j--;
            }
        }
    } else {
        for (int i = left; i <= nums.size() - k; i++) {
            temp.push_back(nums[i]);
            rec_k_sum(nums, i + 1, target - nums[i], k - 1, temp, result);
            temp.pop_back();
        }
    }
}

void rec_k_sum_less(vector<int> &nums, int left, int target, int k, vector<int> &temp, vector<vector<int>> &result)
{
    if (k == 2) {
        int i = left;
        int j = nums.size() - 1;
        while (i < j) {
            if (nums[i] + nums[j] <= target) {
                vector<int> dup1 = temp;
                dup1.push_back(nums[i]);
                dup1.push_back(nums[j]);
                result.push_back(dup1);
                for (int l = j - 1; l > i; l--) {
                    vector<int> dup2 = temp;
                    dup2.push_back(nums[i]);
                    dup2.push_back(nums[l]);
                    result.push_back(dup2);
                }
                i++;
            } else {
                j--;
            }
        }
    } else {
        for (int i = left; i <= nums.size() - k; i++) {
            temp.push_back(nums[i]);
            rec_k_sum_less(nums, i + 1, target - nums[i], k - 1, temp, result);
            temp.pop_back();
        }
    }
}


vector<vector<int>> k_sum(vector<int> &nums, int target, int k)
{
    std::sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    vector<int> temp;
    rec_k_sum(nums, 0, target, k, temp, result);
    return result;
}

vector<vector<int>> k_sum_less(vector<int> &nums, int target, int k)
{
    std::sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    vector<int> temp;
    rec_k_sum_less(nums, 0, target, k, temp, result);
    return result;
}


int main()
{
    vector<int> a = {3, 1, 5, 3, 6, 7, 2, 1, 9, 4};
    for (auto &v:k_sum_less(a, 9, 4)) {
        for (int i : v) {
            cout << i << ',';
        }
        cout << endl;
    }

}