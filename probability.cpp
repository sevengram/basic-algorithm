#include "common.h"

vector<int> rand_select_k_items(vector<int> &stream, int k)
{
    int i;
    vector<int> pool;
    for (i = 0; i < k; i++) {
        pool.push_back(stream[i]);
    }
    srand(time(0));
    for (; i < stream.size(); i++) {
        int j = rand() % (i + 1);
        if (j < k) {
            pool[j] = stream[i];
        }
    }
    return pool;
}

template<typename T>
int insert_index(std::vector<T> &v, T n)
{
    if (v.empty()) {
        return 0;
    }
    int left = 0;
    int right = v.size() - 1;
    while (left < right) {
        int mid = (left + right) / 2;
        if (n < v[mid]) {
            right = mid;
        } else if (n >= v[mid]) {
            left = mid + 1;
        }
    }
    if (n >= v[left]) {
        return left + 1;
    } else {
        return left;
    }
}


int rand_select_one_item(vector<int> &stream)
{
    assert(stream.size() > 0);
    srand(time(0));
    for (int i = 1; i < stream.size(); i++) {
        int j = rand() % (i + 1);
        if (j == 1) {
            return stream[i];
        }
    }
    return stream[0];
}


int rand_select_by_weight(vector<int> &stream)
{
    int n = stream.size();
    if (n == 0) {
        return -1;
    }
    vector<int> accu(n);
    accu[0] = stream[0];
    for (int i = 1; i < n; i++) {
        accu[i] = accu[i - 1] + stream[i];
    }
    srand(time(0));
    int j = rand() % accu[n - 1];
    return insert_index<int>(accu, j);
}

int rand_select_by_float_weight(vector<double> &stream)
{
    int n = stream.size();
    if (n == 0) {
        return -1;
    }
    vector<double> accu(n);
    accu[0] = stream[0];
    for (int i = 1; i < n; i++) {
        accu[i] = accu[i - 1] + stream[i];
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, accu[n - 1]);
    return insert_index<double>(accu, dis(gen));
}
