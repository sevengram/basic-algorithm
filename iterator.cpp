#include "common.h"


class Iterator
{
private:
    const vector<int> data;
    int pos;
public:
    Iterator(const vector<int> &nums) : data{nums}, pos{0}
    {
    }

    Iterator(const Iterator &iter) : data{iter.data}, pos{iter.pos}
    {
    }

    Iterator &operator=(const Iterator &itr)
    {
        auto result = Iterator(itr);
        return result;
    }

    // Returns the next element in the iteration.
    virtual int next()
    {
        assert(hasNext());
        return data[pos++];
    }

    // Returns true if the iteration has more elements.
    virtual bool hasNext() const
    {
        return pos < data.size();
    }
};

class TwistedIterator
{
private:
    bool is_empty;
    int cur;
    vector<Iterator> itrs;
public:
    TwistedIterator(const vector<Iterator> &v)
    {
        itrs.assign(v.begin(), v.end());
        cur = 0;
        is_empty = (v.size() == 0);
    }

    TwistedIterator(const TwistedIterator &iter) : is_empty{iter.is_empty}, cur{iter.is_empty}
    {
        itrs = iter.itrs;
    }

    bool hasNext()
    {
        if (is_empty) {
            return false;
        }
//        int i = 0;
//        while (!itrs[cur].hasNext() && i < itrs.size()) {
//            cur = (cur + 1) % itrs.size();
//            i++;
//        }
//        is_empty = (i == itrs.size());
        while (!itrs[cur].hasNext()) {
            itrs.erase(itrs.begin() + cur);
            if (itrs.empty()) {
                break;
            } else {
                cur = cur % itrs.size();
            }
        }
        is_empty = itrs.empty();
        return !is_empty;
    }

    int next()
    {
        assert(hasNext());
        int result = itrs[cur].next();
        cur = (cur + 1) % itrs.size();
        return result;
    }
};

template<typename T>
class ZigzagIterator
{
private:
    vector<Iterator> iterators;
    int pos;
    int vec_count;

public:
    ZigzagIterator(vector<vector<int>> &vectors) : pos{0}, vec_count{0}
    {
        for (vector<int> &v: vectors) {
            if (v.size() != 0) {
                iterators.push_back(Iterator(v));
                vec_count++;
            }
        }
    }

    bool hasNext() const
    {
        return vec_count > 0;
    }

    int next()
    {
        assert(hasNext());
        while (!iterators[pos].hasNext()) {
            pos = (pos + 1) % iterators.size();
        }
        int result = iterators[pos].next();
        if (!iterators[pos].hasNext()) {
            vec_count--;
        }
        pos = (pos + 1) % iterators.size();
        return result;
    }
};

template<typename T>
class PeekingIterator : public Iterator
{
private:
    bool has_peeked;
    T peeked_item;
public:
    PeekingIterator(const vector<T> &nums) : Iterator(nums)
    {
        has_peeked = false;
    }

    int peek()
    {
        assert(hasNext());
        if (!has_peeked) {
            peeked_item = Iterator::next();
            has_peeked = true;
        }
        return peeked_item;
    }

    virtual int next()
    {
        assert(hasNext());
        if (has_peeked) {
            has_peeked = false;
            return peeked_item;
        } else {
            return Iterator::next();
        }
    }

    virtual bool hasNext()
    {
        return has_peeked || Iterator::hasNext();
    }
};


class BSTIterator
{
private:
    std::stack<TreeNode *> stk;
public:
    BSTIterator(TreeNode *root)
    {
        pushLeft(root);
    }

    bool hasNext()
    {
        return !stk.empty();
    }

    TreeNode *next()
    {
        if (!hasNext()) {
            return nullptr;
        }
        TreeNode *top = stk.top();
        stk.pop();
        pushLeft(top->right);
        return top;
    }

    void pushLeft(TreeNode *n)
    {
        while (n) {
            stk.push(n);
            n = n->left;
        }
    }
};


int main()
{
    Iterator itr1({1, 2, 3, 4, 5});
    Iterator itr2({6, 7, 8, 9});
    Iterator itr3({10, 11, 12, 13});
    vector<Iterator> v;
    v.push_back(itr1);
    v.push_back(itr2);
    v.push_back(itr3);
    TwistedIterator tw(v);
    while (tw.hasNext()) {
        cout << tw.next() << endl;
    }
    return 0;
}