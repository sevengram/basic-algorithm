#include "common.h"

struct Copyable
{
    Copyable() { }

    Copyable(const Copyable &o)
    {
        cout << "Copied" << endl;
    }

    Copyable(Copyable &&o)
    {
        cout << "Moved" << endl;
    }
};

Copyable returnRvalue()
{
    return Copyable();
}

void acceptVal(Copyable)
{
}

void acceptConstRef(const Copyable &)
{
}

void acceptRvalueRef(Copyable &&s)
{
    Copyable news = std::move(s);
}

int main()
{
    cout << "Pass by value: " << endl;
    acceptVal(returnRvalue());
    cout << "Pass by const left reference: " << endl;
    acceptConstRef(returnRvalue());
    cout << "Pass by right reference: " << endl;
    acceptRvalueRef(returnRvalue());
    return 0;
}