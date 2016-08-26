#include "common.h"


class EmptyVectorException : public exception
{
public:
    virtual const char *what()
    {
        return "empty vector";
    }
};


int sumVector(vector<int> &v) throw(EmptyVectorException)
{
    if (v.empty()) {
        throw EmptyVectorException();
    }
    int result = 0;
    for (int i:v) {
        result += i;
    }
    return result;
}

int main()
{
    vector<int> v;
    try {
        sumVector(v);
    } catch (EmptyVectorException e) {
        cout << e.what() << endl;
    }
    return 0;
}