#include "common.h"

int find_subarray_max_sum(vector<int> &v)
{
    int max_sum = v[0];
    int local_sum = 0;
    for (int i = 0; i < v.size(); i++) {
        local_sum += v[i];
        if (local_sum > max_sum) {
            max_sum = local_sum;
        }
        if (local_sum < 0) {
            local_sum = 0;
        }
    }
    return max_sum;
}

int find_longest_lt_target(vector<int> &v, int target)
{
    int result = 0;
    for (int i = 0; i < v.size(); i++) {
        int sum = 0;
        for (int j = i; j < v.size(); j++) {
            sum += v[j];
            if (sum <= target) {
                result = max(result, j - i + 1);
            }
        }
    }
    return result;
}

int find_longest_lt_target_non_negative(vector<int> &v, int target)
{
    int j = 0;
    int i = 0;
    int sum = 0;
    int result = 0;
    for (; j < v.size(); j++) {
        sum += v[j];
        if (sum > target) {
            result = max(result, j - i);
            while (sum > target) {
                sum -= v[i++];
            }
        }
    }
    if (sum <= target) {
        result = max(result, j - i);
    }
    return result;
}


int find_submatrix_max_sum(vector<vector<int>> &mtx)
{
    int m = mtx.size();
    int n = mtx[0].size();
    vector<vector<int>> sum = mtx;
    for (int i = 1; i < m; i++) {
        for (int j = 0; j < n; j++) {
            sum[i][j] += sum[i - 1][j];
        }
    }
    vector<int> result(n);
    int global_max = mtx[0][0];
    for (int i = 0; i < m; i++) {
        for (int k = i; k < m; k++) {
            for (int j = 0; j < n; j++) {
                result[j] = (i == 0) ? sum[k][j] : (sum[k][j] - sum[i - 1][j]);
            }
            global_max = max(find_subarray_max_sum(result), global_max);
        }
    }
    return global_max;
}

int find_largest_submatrix_lt_target(vector<vector<int>> &mtx, int target)
{
    int m = mtx.size();
    int n = mtx[0].size();
    vector<vector<int>> sum = mtx;
    for (int i = 1; i < m; i++) {
        for (int j = 0; j < n; j++) {
            sum[i][j] += sum[i - 1][j];
        }
    }
    vector<int> result(n);
    int global_max = 0;
    for (int i = 0; i < m; i++) {
        for (int k = i; k < m; k++) {
            for (int j = 0; j < n; j++) {
                result[j] = (i == 0) ? sum[k][j] : (sum[k][j] - sum[i - 1][j]);
            }
            global_max = max(global_max, find_longest_lt_target(result, target) * (k - i + 1));
        }
    }
    return global_max;
}