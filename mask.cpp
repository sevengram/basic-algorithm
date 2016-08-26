#include "common.h"

vector<int> addOne(vector<int> &num)
{
    int overflow = 1;
    int n = num.size();
    vector<int> result(n);
    int sum;
    for (int i = n - 1; i >= 0; i--) {
        sum = num[i] + overflow;
        overflow = sum / 10;
        result[i] = sum % 10;
    }
    if (overflow != 0) {
        result.insert(result.begin(), overflow);
    }
    return result;
}

bool isOn(int index, vector<long> &lights)
{
    size_t n = lights.size() * sizeof(long);
    if (index >= n) {
        return false;
    }
    size_t vi = index / sizeof(long);
    size_t bi = index % sizeof(long);
    return ((lights[vi] >> bi) & 0x1) == 0x1;
}

void toggle(int start, int end, vector<long> &lights)
{
    if (start > end) {
        return;
    }
    int sl = sizeof(long);

    int vs = start / sl;
    int bs = start % sl;
    int ve = end / sl;
    int be = end % sl;

    if (ve == vs) {
        long mask = ~0L << bs & (be != (sl - 1) ? ~(~0L << (be + 1)) : ~0L);
        lights[ve] ^= mask;
    } else {
        int low = (bs == 0) ? vs : vs + 1;
        int high = (be == sl - 1) ? ve : ve - 1;
        for (int i = low; i <= high; i++) {
            lights[i] = ~lights[i];
        }
        if (bs != 0) {
            long mask = ~0L << bs;
            lights[vs] ^= mask;
        }
        if (be != sl - 1) {
            long mask = be != (sl - 1) ? ~(~0L << (be + 1)) : ~0L;
            lights[ve] ^= mask;
        }
    }
}


int main()
{
    return 0;
}