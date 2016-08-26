#include "common.h"

// 1. Insertion Sort
// Best: O(n)
// Average: O(n^2)
// Worst: O(n^2)
// Stable: Y
void insertion_sort(vector<int> &v)
{
    for (int i = 1; i < v.size(); i++) {
        int key = v[i];
        int j;
        for (j = i - 1; j >= 0 && v[j] > key; j--) {
            v[j + 1] = v[j];
        }
        v[j + 1] = key;
    }
}

// 2. Shell Sort
// Stable: N
void shell_sort(vector<int> &v)
{
    int n = v.size();
    int gap = n / 2;
    while (gap > 0) {
        for (int i = gap; i < n; i++) {
            int key = v[i];
            int j;
            for (j = i - gap; j >= 0 && v[j] > key; j -= gap) {
                v[j + gap] = v[j];
            }
            v[j + gap] = key;
        }
        gap = (gap == 2 ? 1 : (int) (gap / 2.2));
    }
}

// 3. Selection Sort
// Best: O(n^2)
// Average: O(n^2)
// Worst: O(n^2)
// Stable: N
void selection_sort(vector<int> &v)
{
    int n = v.size();
    for (int i = 0; i < n - 1; i++) {
        int min_i = i;
        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[min_i]) {
                min_i = j;
            }
        }
        swap(v[i], v[min_i]);
    }
}


// 4. Bubble Sort
// Best: O(n)
// Average: O(n^2)
// Worst: O(n^2)
// Stable: Y
void bubble_sort(vector<int> &v)
{
    int n = v.size();
    for (int i = 0; i < n - 1; i++) {
        bool ordered = true;
        for (int j = 0; j < n - 1 - i; j++) {
            if (v[j + 1] < v[j]) {
                swap(v[j + 1], v[j]);
                ordered = false;
            }
        }
        if (ordered) {
            return;
        }
    }
}

// 5. Merge Sort
// Best: O(nlgn)
// Average: O(nlgn)
// Worst: O(nlgn)
// Stable: Y
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

// 6. Quick Sort
// Best: O(nlgn)
// Average: O(nlgn)
// Worst: O(n^2)
// Stable: N
int partition(vector<int> &v, int l, int r)
{
    if (l == r - 1) {
        return l;
    }
    int pivot = v[l];
    int i = l;
    for (int j = l + 1; j < r; j++) {
        if (v[j] < pivot) {
            swap(v[++i], v[j]);
        }
    }
    swap(v[i], v[l]);
    return i;
}


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

// 7. Heap Sort
// Best: O(nlgn)
// Average: O(nlgn)
// Worst: O(nlgn)
// Stable: N
void max_heap_fix_down(vector<int> &v, int i, int n)
{
    int tmp = v[i];
    int j = 2 * i + 1;
    while (j < n) {
        if (j != n - 1 && v[j] < v[j + 1]) {
            j++;
        }
        if (tmp >= v[j]) {
            break;
        }
        v[i] = v[j];
        i = j;
        j = 2 * i + 1;
    }
    v[i] = tmp;
}

void heap_sort(vector<int> &v)
{
    int n = v.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        max_heap_fix_down(v, i, n);
    }
    for (int i = n - 1; i >= 0; i--) {
        swap(v[0], v[i]);
        max_heap_fix_down(v, 0, i);
    }
}

// 8. Counting Sort
void counting_sort(vector<int> &v)
{
    vector<int> c;
    for (int m:v) {
        if (m >= c.size()) {
            c.resize(m + 1, 0);
        }
        c[m]++;
    }
    for (int i = 1; i < c.size(); i++) {
        c[i] += c[i - 1];
    }
    vector<int> u = v;
    for (int m: u) {
        v[c[m] - 1] = m;
        c[m]--;
    }
}

int main()
{
    vector<int> v = {9, 500, 3, 5, 4, 3, 3, 7, 10, 2, 7};
    counting_sort(v);
    for (int n:v) {
        cout << n << ", ";
    }
    cout << endl;
    v = {};
    counting_sort(v);
    return 0;
}
