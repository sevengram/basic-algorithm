#include "common.h"

int partition(vector<int> &v, int l, int r, bool asc = true)
{
    if (l == r - 1) {
        return l;
    }
    int pivot = v[l];
    int i = l;
    for (int j = l + 1; j < r; j++) {
        if ((v[j] < pivot && asc) || (v[j] > pivot && !asc)) {
            swap(v[++i], v[j]);
        }
    }
    swap(v[i], v[l]);
    return i;
}

/*
 * select kth
 */
int rec_select_kth(vector<int> &v, int l, int r, int k)
{
    int p = partition(v, l, r);
    int rp = p - l + 1;
    if (k == rp) {
        return v[p];
    } else if (k < rp) {
        return rec_select_kth(v, l, p, k);
    } else {
        return rec_select_kth(v, p + 1, r, k - rp);
    }
}

int select_kth(vector<int> &v, int k)
{
    return rec_select_kth(v, 0, v.size(), k);
}

/*
 * select all first kth
 */
void rec_select_all_first_kth(vector<int> &v, int l, int r, int k, vector<int> &result, bool asc)
{
    int p = partition(v, l, r, asc);
    int rp = p - l + 1;
    if (k == rp) {
        result.insert(result.end(), v.begin() + l, v.begin() + p + 1);
        return;
    } else if (k < rp) {
        rec_select_all_first_kth(v, l, p, k, result, asc);
    } else {
        result.insert(result.end(), v.begin() + l, v.begin() + p + 1);
        rec_select_all_first_kth(v, p + 1, r, k - rp, result, asc);
    }
}

vector<int> select_all_first_kth(vector<int> &v, int k, bool asc)
{
    vector<int> result;
    rec_select_all_first_kth(v, 0, v.size(), k, result, asc);
    return result;
}

/*
 * Quick sort
 */
void rec_quick_sort(vector<int> &v, int l, int r)
{
    if (l < r - 1) {
        int p = partition(v, l, r);
        rec_quick_sort(v, l, p);
        rec_quick_sort(v, p + 1, r);
    }
}

void quick_sort(vector<int> &v)
{
    rec_quick_sort(v, 0, v.size());
}

/*
 * Merge sort
 */
void merge(vector<int> &v, int l, int m, int r)
{
    vector<int> v1(v.begin() + l, v.begin() + m);
    vector<int> v2(v.begin() + m, v.begin() + r);
    int i = 0;
    int j = 0;
    for (int k = l; k < r; k++) {
        if (i == m - l) {
            v[k] = v2[j++];
        } else if (j == r - m) {
            v[k] = v1[i++];
        } else {
            if (v1[i] < v2[j]) {
                v[k] = v1[i++];
            } else {
                v[k] = v2[j++];
            }
        }
    }
}

void rec_merge_sort(vector<int> &v, int l, int r)
{
    if (l < r - 1) {
        int m = (l + r) / 2;
        rec_merge_sort(v, l, m);
        rec_merge_sort(v, m, r);
        merge(v, l, m, r);
    }
}

void merge_sort(vector<int> &v)
{
    rec_merge_sort(v, 0, v.size());
}

int select_kth_in_two_sorted(int *a, int m, int *b, int n, int k)
{
    if (m > n) {
        return select_kth_in_two_sorted(b, n, a, m, k);
    }
    if (m == 0) {
        return b[k - 1];
    }
    if (k == 1) {
        return a[0] < b[0] ? a[0] : b[0];
    }
    int pa = k / 2 < m ? k / 2 : m;
    int pb = k - pa;
    if (a[pa - 1] < b[pb - 1]) {
        return select_kth_in_two_sorted(a + pa, m - pa, b, n, k - pa);
    } else if (a[pa - 1] > b[pb - 1]) {
        return select_kth_in_two_sorted(a, m, b + pb, n - pb, k - pb);
    } else {
        return a[pa - 1];
    }
}
