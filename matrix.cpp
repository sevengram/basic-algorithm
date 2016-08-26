#include "common.h"

void rec_change(vector<vector<char>> &grid, vector<vector<bool>> &visited, int i, int j)
{
    if (grid.empty() || grid[0].empty()) {
        return;
    }
    int m = grid.size();
    int n = grid[0].size();
    if (!(i < 0 || i >= m || j < 0 || j >= n) && grid[i][j] == '1' && !visited[i][j]) {
        visited[i][j] = true;
        if (i + 1 < m) {
            rec_change(grid, visited, i + 1, j);
        }
        if (i - 1 >= 0) {
            rec_change(grid, visited, i - 1, j);
        }
        if (j + 1 < n) {
            rec_change(grid, visited, i, j + 1);
        }
        if (j - 1 < n) {
            rec_change(grid, visited, i, j - 1);
        }
    }
}
