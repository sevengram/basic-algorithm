#include "common.h"

void init(std::vector<int> &sets)
{
    sets.assign(sets.size(), -1);
}

int find_root(int x, std::vector<int> &sets)
{
    if (sets[x] < 0) {
        return x;
    } else {
        return sets[x] = find_root(sets[x], sets); // path compression
    }
}

void join(int x, int y, std::vector<int> &sets)
{
    int rx = find_root(x, sets);
    int ry = find_root(y, sets);
    if (rx != ry) {
        sets[rx] = ry;
    }
}