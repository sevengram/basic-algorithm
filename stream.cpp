//
// Created by jfan on 8/1/16.
//

#include "common.h"

string longestSubstringKDistinct(stringstream &ss, int k)
{
    list<char> q;
    int max_length = 0;
    string result;
    unordered_map<char, int> count_map;
    int count = 0;
    char c;
    bool reset = true;
    while (ss.read(&c, 1)) {
        if (++count_map[c] == 1) {
            count++;
        }
        q.push_back(c);
        if (count > k) {
            if (--count_map[q.front()] == 0) {
                count--;
            }
            q.pop_front();
            reset = true;
        } else {
            if (q.size() > max_length) {
                max_length = q.size();
                if (reset) {
                    result = string(q.begin(), q.end());
                    reset = false;
                } else {
                    result += c;
                }
            }
        }
    }
    return result;
}


string longestSubstringWithoutDuplicates(stringstream &ss)
{
    list<char> q;
    int max_length = 0;
    string result;
    unordered_map<char, bool> exist_map;
    char c;
    int reset = true;
    while (ss.read(&c, 1)) {
        while (exist_map[c] == true) {
            reset = true;
            exist_map[q.front()] = false;
            q.pop_front();
        }
        q.push_back(c);
        exist_map[c] = true;
        if (q.size() > max_length) {
            max_length = q.size();
            if (reset) {
                result = string(q.begin(), q.end());
                reset = false;
            } else {
                result += c;
            }
        }
    }
    return result;
}


class MedianFinder
{
private:
    priority_queue<int> max_heap;
    priority_queue<int, vector<int>, greater<int>> min_heap;

public:
    // Adds a number into the data structure.
    void addNum(int num)
    {
        if (max_heap.empty()) {
            max_heap.push(num);
        } else if (num < max_heap.top()) {
            max_heap.push(num);
        } else {
            min_heap.push(num);
        }
        int m = max_heap.size();
        int n = min_heap.size();
        if (m - n == 2) {
            min_heap.push(max_heap.top());
            max_heap.pop();
        } else if (n - m == 2) {
            max_heap.push(min_heap.top());
            min_heap.pop();
        }
    }

    // Returns the median of current data stream
    double findMedian()
    {
        int m = max_heap.size();
        int n = min_heap.size();
        if (m == 0 && n == 0) {
            return -1;
        }
        if (m == n) {
            return (max_heap.top() + min_heap.top()) / 2.0;
        } else if (m > n) {
            return max_heap.top();
        } else {
            return min_heap.top();
        }
    }
};

class MovingAverage
{
private:
    int size;
    int sum;
    queue<int> q;
public:
    MovingAverage(int size)
    {
        this->size = size;
        this->sum = 0;
    }

    void addNum(int num)
    {
        if (q.size() == size) {
            sum -= q.front();
            q.pop();
        }
        q.push(num);
        sum += num;
    }

    double findAverage()
    {
        return (double) sum / size;
    }
};

struct Interval
{
    int start;
    int end;

    Interval() : start(0), end(0) { }

    Interval(int s, int e) : start(s), end(e) { }
};

class SummaryRanges
{
private:
    struct Cmp
    {
        bool operator()(const Interval &a, const Interval &b)
        {
            return a.start < b.start;
        }
    };

    set<Interval, Cmp> s;

public:
    /** Initialize your data structure here. */
    SummaryRanges()
    {
    }

    void addNum(int val)
    {
        int start = val;
        int end = val;
        set<Interval>::iterator p, q;
        p = q = s.lower_bound(Interval(start, end));
        if (q != s.begin() && (--q)->end >= start - 1) {
            p--;
        }
        while (p != s.end() && p->start <= end + 1) {
            start = min(start, p->start);
            end = max(end, p->end);
            p = s.erase(p);
        }
        s.insert(p, Interval(start, end));
    }

    vector<Interval> getIntervals()
    {
        return vector<Interval>(s.begin(), s.end());
    }
};


int main()
{
    stringstream ss;
    ss.str("helltoooooo1111111111p111m111ksdfe99999ee");
    cout << longestSubstringKDistinct(ss, 3) << endl;
    stringstream ss2;
    ss2.str("helltoooooo1111111111p111111ksdfe99999ee");
    cout << longestSubstringWithoutDuplicates(ss2) << endl;
    return 0;
}