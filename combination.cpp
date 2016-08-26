#include "common.h"

void rec_comb(int k, int start, vector<int> &nums, std::vector<std::vector<int>> &result, std::vector<int> &combine)
{
    int n = nums.size();
    if (k < 0 || n - start <= k) {
        return;
    }
    for (int i = start; i < n; i++) {
        combine[k] = nums[i];
        if (k > 0) {
            rec_comb(k - 1, i + 1, nums, result, combine);
        } else {
            result.push_back(combine);
        }
    }
}

std::vector<std::vector<int>> combine(vector<int> &nums, int k)
{
    std::vector<std::vector<int>> result;
    if (nums.size() < k) {
        return result;
    }
    std::vector<int> combine(k);
    rec_comb(k - 1, 0, nums, result, combine);
    return result;
}


void rec_perm(int depth, vector<int> &nums, vector<vector<int>> &result)
{
    int n = nums.size();
    for (int i = depth; i < n; i++) {
        swap(nums[i], nums[depth]);
        if (depth == n - 1) {
            result.push_back(nums);
        } else {
            rec_perm(depth + 1, nums, result);
        }
        swap(nums[i], nums[depth]);
    }
}

vector<vector<int> > permute(vector<int> &nums)
{
    vector<vector<int>> result;
    rec_perm(0, nums, result);
    return result;
}

void perm_search(int k, int start, vector<int> &nums, vector<vector<int>> &result,
                 vector<int> &combine)
{
    int n = nums.size();
    if (k < 0 || n - start <= k) {
        return;
    }
    for (int i = start; i < n; i++) {
        combine[k] = nums[i];
        if (k > 0) {
            perm_search(k - 1, i + 1, nums, result, combine);
        } else {
            rec_perm(0, combine, result);
        }
    }
}

vector<vector<int> > permute_part(vector<int> &nums, int k)
{
    vector<vector<int>> result;
    if (nums.size() < k) {
        return result;
    }
    vector<int> combine(k);
    perm_search(k - 1, 0, nums, result, combine);
    return result;
}


void rec_possible_strs(string &s, int i, const string &options, vector<string> &result)
{
    if (s.size() == i) {
        result.push_back(s);
        return;
    }
    if (s[i] == '*') {
        for (char c:options) {
            s[i] = c;
            rec_possible_strs(s, i + 1, options, result);
        }
        s[i] = '*';
    } else {
        rec_possible_strs(s, i + 1, options, result);
    }
}

vector<string> possible_strs(string &s, string options)
{
    vector<string> result;
    rec_possible_strs(s, 0, options, result);
    return result;
}

void recStrobogrammatic(const string &str, int n, vector<string> &result)
{
    if (n == 0) {
        result.push_back(str);
        return;
    }
    if (n % 2 == 1) {
        recStrobogrammatic("0", n - 1, result);
        recStrobogrammatic("1", n - 1, result);
        recStrobogrammatic("8", n - 1, result);
        return;
    }
    if (n != 2) {
        recStrobogrammatic("0" + str + "0", n - 2, result);
    }
    recStrobogrammatic("1" + str + "1", n - 2, result);
    recStrobogrammatic("8" + str + "8", n - 2, result);
    recStrobogrammatic("6" + str + "9", n - 2, result);
    recStrobogrammatic("9" + str + "6", n - 2, result);
}

vector<string> getAllStrobogrammatic(int n)
{
    vector<string> result;
    recStrobogrammatic("", n, result);
    return result;
}

vector<string> getAllStrobogrammatic2(int n)
{
    if (n == 0) {
        return {};
    }
    queue<string> q;
    if (n % 2 == 1) {
        q.push("1");
        q.push("0");
        q.push("8");
        n--;
    } else {
        q.push("");
    }
    while (n > 0) {
        int m = q.size();
        for (int i = 0; i < m; i++) {
            string s = q.front();
            q.pop();
            q.push("0" + s + "0");
            q.push("1" + s + "1");
            q.push("8" + s + "8");
            q.push("6" + s + "9");
            q.push("9" + s + "6");
        }
        n -= 2;
    }
    vector<string> v;
    while (!q.empty()) {
        v.push_back(q.front());
        q.pop();
    }
    return v;
}


void recSearch(string &s, int num, int pos, const string &path, vector<string> &result)
{
    int n = s.size();
    if (pos == n) {
        if (num == 4) {
            result.push_back(path.substr(0, path.size() - 1));
        }
        return;
    }

    if (n - pos > 3 * (4 - num))
        return;

    if (pos <= n - 1) {
        recSearch(s, num + 1, pos + 1, path + s.substr(pos, 1) + ".", result);
    }
    if (pos <= n - 2 && s[pos] != '0') {
        recSearch(s, num + 1, pos + 2, path + s.substr(pos, 2) + ".", result);
    }
    if (pos <= n - 3 && s[pos] != '0' && s.substr(pos, 3) <= "255") {
        recSearch(s, num + 1, pos + 3, path + s.substr(pos, 3) + ".", result);
    }
}

vector<string> restoreIpAddresses(string s)
{
    vector<string> result;
    recSearch(s, 0, 0, "", result);
    return result;
}

void recGenerate(int l, int r, const string &s, vector<string> &result)
{
    if (l < 0 || r < l) {
        return;
    }
    if (l == 0 && r == 0) {
        result.push_back(s);
    }
    if (l > 0) {
        recGenerate(l - 1, r, s + '(', result);
    }
    if (r > l) {
        recGenerate(l, r - 1, s + ')', result);
    }
}

vector<string> generateParenthesis(int n)
{
    vector<string> result;
    recGenerate(n, n, "", result);
    return result;
}

void dfs(vector<int> &candidates, int target, int index, vector<int> &nums, vector<vector<int>> &res)
{
    for (int i = index; i < candidates.size() && candidates[i] <= target; i++) {
        if (i > index && candidates[i - 1] == candidates[i]) {
            continue;
        }
        nums.push_back(candidates[i]);
        if (target == candidates[i]) {
            res.push_back(nums);
        } else {
            dfs(candidates, target - candidates[i], i, nums, res);
        }
        nums.pop_back();
    }
}

vector<vector<int>> combinationSum(vector<int> &candidates, int target)
{
    vector<vector<int>> result;
    vector<int> nums;
    sort(candidates.begin(), candidates.end());
    dfs(candidates, target, 0, nums, result);
    return result;
}


// n queens
bool isOk(const vector<string> &m, int x, int y, int n)
{
    for (int i = 0; i < x; i++) {
        if (m[i][y] == 'Q') {
            return false;
        }
    }
    int i = x;
    int j = y;
    while (--i >= 0 && --j >= 0) {
        if (m[i][j] == 'Q') {
            return false;
        }
    }
    i = x;
    j = y;
    while (--i >= 0 && ++j < n) {
        if (m[i][j] == 'Q') {
            return false;
        }
    }
    return true;
}

void recSearch(vector<string> &m, int x, int n, vector<vector<string>> &result)
{
    for (int y = 0; y < n; y++) {
        m[x][y] = 'Q';
        if (isOk(m, x, y, n)) {
            if (x == n - 1) {
                result.push_back(m);
            } else {
                recSearch(m, x + 1, n, result);
            }
        }
        m[x][y] = '.';
    }
}

vector<vector<string>> solveNQueens(int n)
{
    vector<vector<string>> result;
    vector<string> m(n, string(n, '.'));
    recSearch(m, 0, n, result);
    return result;
}

void findSets(vector<int> &s, int start, vector<int> &subset, vector<vector<int>> &result)
{
    result.push_back(subset);
    for (int i = start; i < s.size(); i++) {
        if (i != start && s[i] == s[i - 1]) {
            continue;
        }
        subset.push_back(s[i]);
        findSets(s, i + 1, subset, result);
        subset.pop_back();
    }
}

vector<vector<int>> subsetsWithDup(std::vector<int> &s)
{
    vector<vector<int>> result;
    sort(s.begin(), s.end());
    vector<int> subset;
    findSets(s, 0, subset, result);
    return result;
}

void recSearchPathSum(TreeNode *n, int sum, vector<vector<int>> &result, vector<int> &path)
{
    if (n == nullptr) {
        return;
    }
    path.push_back(n->val);
    if (!n->left && !n->right) {
        if (n->val == sum) {
            result.push_back(path);
        }
    } else {
        if (n->left) {
            recSearchPathSum(n->left, sum - n->val, result, path);
        }
        if (n->right) {
            recSearchPathSum(n->right, sum - n->val, result, path);
        }
    }
    path.pop_back();
}

vector<vector<int>> pathSum(TreeNode *root, int sum)
{
    vector<vector<int>> result;
    vector<int> path;
    recSearchPathSum(root, sum, result, path);
    return result;
}

int main()
{
    for (string s:getAllStrobogrammatic2(3)) {
        cout << s << endl;
    }
    return 0;
}