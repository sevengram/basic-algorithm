#include "rotation.h"

void rotate_matrix_clockwise(vector<vector<int>> &mtx)
{
    int n = mtx.size();
    for (int layer = 0; layer < n / 2; layer++) {
        int first = layer;
        int last = n - layer - 1;
        for (int i = first; i < last; i++) {
            int offset = i - first;
            int t = mtx[first][i];
            mtx[first][i] = mtx[last - offset][first];
            mtx[last - offset][first] = mtx[last][last - offset];
            mtx[last][last - offset] = mtx[i][last];
            mtx[i][last] = t;
        }
    }
}

void rotate_matrix_counter_clockwise(vector<vector<int>> &mtx)
{
    int n = mtx.size();
    for (int layer = 0; layer < n / 2; layer++) {
        int first = layer;
        int last = n - layer - 1;
        for (int i = first; i < last; i++) {
            int offset = i - first;
            int t = mtx[first][i];
            mtx[first][i] = mtx[i][last];
            mtx[i][last] = mtx[last][last - offset];
            mtx[last][last - offset] = mtx[last - offset][first];
            mtx[last - offset][first] = t;
        }
    }
}
