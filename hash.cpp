#include "common.h"


unsigned long time33_hashing(string str)
{
    unsigned long result = 5381;
    for (char c:str) {
        result = ((result << 5) + result) + c; /* hash * 33 + c */
    }
    return result;
}

int main()
{
    cout << time33_hashing("hello") << endl;
    return 0;
}