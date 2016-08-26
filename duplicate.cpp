#include "common.h"

void remove_duplicates_sorted(vector<int> &nums)
{
    if (nums.empty()) {
        return;
    }
    int j = 1;
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] != nums[j - 1]) {
            nums[j++] = nums[i];
        }
    }
    nums.erase(nums.begin() + j, nums.end());
}

void remove_duplicates_unsorted(vector<int> &nums)
{
    if (nums.empty()) {
        return;
    }
    int j = 1;
    std::unordered_set<int> s;
    s.insert(nums[0]);
    for (int i = 1; i < nums.size(); i++) {
        if (s.find(nums[i]) == s.end()) {
            s.insert(nums[i]);
            nums[j++] = nums[i];
        }
    }
    nums.erase(nums.begin() + j, nums.end());
}

/*
 * 316. Remove Duplicate Letters
 */
string removeChar(const string &s, int start, char c)
{
    string result;
    for (int j = start; j < s.size(); j++) {
        if (s[j] != c) {
            result += s[j];
        }
    }
    return result;
}

string removeDuplicateLetters(string s)
{
    if (s.size() == 0) {
        return s;
    }
    vector<int> count(26, 0);
    for (char c: s) {
        count[c - 'a']++;
    }
    int pos = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] < s[pos]) {
            pos = i;
        }
        if (--count[s[i] - 'a'] == 0) {
            break;
        }
    }
    return s[pos] + removeDuplicateLetters(removeChar(s, pos + 1, s[pos]));
}