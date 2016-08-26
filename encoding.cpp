#include "common.h"

string char_count_encoding(const string &s)
{
    string result;
    vector<int> a = string2vector(s);
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != 0) {
            result.push_back('a' + i);
            result.push_back('0' + a[i]);
        }
    }
    return result;
}

vector<int> string2vector(const string &s)
{
    string s1;
    s1.resize(s.size());
    transform(s.begin(), s.end(), s1.begin(), ::tolower);
    vector<int> a(26, 0);
    for (char c:s1) {
        a[c - 'a'] += 1;
    }
    return a;
}

int string2bits(const string &s)
{
    string s1;
    s1.resize(s.size());
    transform(s.begin(), s.end(), s1.begin(), ::tolower);
    int result = 0;
    for (char c:s1) {
        result = set_bit(result, c - 'a');
    }
    return result;
}

bool no_same_char(const string &s1, const string &s2)
{
    return (string2bits(s1) & string2bits(s2)) == 0;
}