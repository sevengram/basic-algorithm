#include "common.h"

// leetcodee 30
// 30. Substring with Concatenation of All Words
vector<int> findSubstring(string s, vector<string> &words)
{
    vector<int> result;
    if (s.empty() || words.empty()) {
        return result;
    }
    unordered_map<string, int> words_map;
    for (string w:words) {
        words_map[w]++;
    }
    int count = words.size();
    int len = words[0].size();
    unordered_map<string, int> counting;
    for (int i = 0; i <= (int) (s.size()) - len * count; i++) {
        counting.clear();
        int j;
        for (j = 0; j < count; j++) {
            string w = s.substr(i + j * len, len);
            if (words_map.find(w) != words_map.end()) {
                counting[w]++;
                if (counting[w] > words_map[w]) {
                    break;
                }
            } else {
                break;
            }
        }
        if (j == count) {
            result.push_back(i);
        }
    }
    return result;
}

bool is_covered(unordered_map<char, int> &s_chars, unordered_map<char, int> &t_chars)
{
    for (auto itr = t_chars.begin(); itr != t_chars.end(); itr++) {
        if (itr->second > s_chars[itr->first]) {
            return false;
        }
    }
    return true;
}

string minWindow(string s, string t)
{
    if (s.empty() || t.empty()) {
        return "";
    }
    int min_length = s.size() + 1;
    int min_start = 0;
    unordered_map<char, int> t_chars;
    for (char c:t) {
        t_chars[c]++;
    }
    unordered_map<char, int> s_chars;
    int j = 0;
    for (int i = 0; i < s.size(); i++) {
        while (!is_covered(s_chars, t_chars) && j < s.size()) {
            s_chars[s[j]]++;
            j++;
        }
        if (is_covered(s_chars, t_chars)) {
            if (j - i + 1 < min_length) {
                min_length = j - i + 1;
                min_start = i;
            }
        }
        s_chars[s[i]]--;
    }
    return min_length <= s.size() ? s.substr(min_start, min_length) : "";
}

//有一个整型数组 arr 和一个大小为 w 的窗口从数组的最左边滑到最右边,窗口每次向右边滑一个位置.
//返回一个长度为 n-w+1的数组res, res[i]表示每一种窗口状态下的最大值.
vector<int> slideWindowMax(const vector<int> &arr, int w)
{
    if (arr.size() == 0 || w == 0 || w > arr.size()) {
        return {};
    }
    deque<int> index_queue; // increasing data
    vector<int> result;
    for (int i = 0; i < arr.size(); i++) {
        while (!index_queue.empty() && arr[index_queue.back()] <= arr[i]) {
            index_queue.pop_back();
        }
        index_queue.push_back(i);
        if (index_queue.front() == i - w) {
            index_queue.pop_front();
        }
        if (i >= w - 1) {
            result.push_back(arr[index_queue.front()]);
        }
    }
    return result;
}

int maxLengthforUniqueNumbers(const vector<int> &arr)
{
    int n = arr.size();
    if (n <= 1) {
        return n;
    }
    int i = 0;
    int j = 0;
    int result = 0;
    unordered_set<int> record;
    while (j < n) {
        while (record.find(arr[j]) == record.end() && j < n) {
            record.insert(arr[j++]);
        }
        result = max(result, j - i);
        record.erase(arr[i++]);
    }
    return result;
}