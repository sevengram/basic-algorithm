#include "common.h"
#include <algorithm>
#include <cassert>

using namespace std;

int knapsack_problem_01(vector<int> &weight, vector<int> &price, int capacity, vector<int> &items)
{
    int n = weight.size();
    vector<vector<int>> t(n + 1, vector<int>(capacity + 1, 0));
    vector<vector<int>> path(n + 1, vector<int>(capacity + 1, 0));
    for (int i = 1; i <= n; i++) {
        int w = weight[i - 1];
        int p = price[i - 1];
        for (int j = 1; j <= capacity; j++) {
            if (w <= j && t[i - 1][j] < t[i - 1][j - w] + p) {
                t[i][j] = t[i - 1][j - w] + p;
                path[i][j] = 1;
            } else {
                t[i][j] = t[i - 1][j];
            }
        }
    }
    items.clear();
    int i = n;
    int j = capacity;
    while (i > 0 && j > 0) {
        if (path[i][j] == 1) {
            items.push_back(i - 1);
            j -= weight[i - 1];
        }
        i--;
    }
    return t[n][capacity];
}

int knapsack_problem_01_compress(vector<int> &weight, vector<int> &price, int capacity,
                                 vector<int> &items)
{
    int n = weight.size();
    vector<int> t(capacity + 1, 0);
    vector<vector<int>> path(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        int w = weight[i - 1];
        int p = price[i - 1];
        for (int j = capacity; j >= w; j--) {
            if (t[j] < t[j - w] + p) {
                t[j] = t[j - w] + p;
                path[i][j] = 1;
            }
        }
    }
    items.clear();
    int i = n;
    int j = capacity;
    while (i > 0 && j > 0) {
        if (path[i][j] == 1) {
            items.push_back(i - 1);
            j -= weight[i - 1];
        }
        i--;
    }
    return t[capacity];
}

int knapsack_problem_complete(vector<int> &weight, vector<int> &price, int capacity, vector<int> &items)
{
    int n = weight.size();
    vector<int> t(capacity + 1, 0);
    vector<int> path(capacity + 1, -1);

    for (int i = 1; i <= n; i++) {
        int w = weight[i - 1];
        int p = price[i - 1];
        for (int j = w; j <= capacity; j++) {
            if (t[j] < t[j - w] + p) {
                t[j] = t[j - w] + p;
                path[j] = i - 1;
            }
        }
    }
    items.clear();
    int j = capacity;
    while (j > 0 && path[j] >= 0) {
        items.push_back(path[j]);
        j -= weight[path[j]];
    }
    return t[capacity];
}

int climb_stairs(int n)
{
    vector<int> v(n + 2, 0);
    v[1] = 1;
    v[2] = 2;
    for (int i = 3; i <= n; i++) {
        v[i] = v[i - 1] + v[i - 2];
    }
    return v[n];
}

int numTrees(int n)
{
    if (n == 0 || n == 1) {
        return 1;
    }
    vector<int> v(n + 1, 0);
    v[0] = 1;
    v[1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            v[i] += v[j] * v[i - 1 - j];
        }
    }
    return v[n];
}

int max_sum_skip(vector<int> &v)
{
    int n = v.size();
    if (n == 0) {
        return -1; // or throw error
    }
    vector<int> result(n + 1);
    result[0] = 0;
    result[1] = v[0];
    for (int i = 2; i <= n; i++) {
        result[i] = max(result[i - 2] + v[i], result[i - 1]);
    }
    return result[n];
}

/*
 * 3. Longest Increasing Subsequence
 */
int lengthOfLIS(vector<int> &nums)
{
    int n = nums.size();
    if (n == 0) {
        return 0;
    }
    vector<int> dp(n, 1);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[i] > nums[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    return *max_element(dp.begin(), dp.end());
}

int recSearch(vector<vector<int>> &mtx, int i, int j, vector<vector<int>> &memorized_record)
{
    int m = mtx.size();
    assert(m > 0);
    int n = mtx[0].size();
    assert(n > 0);
    int result = 0;
    if (memorized_record[i][j] > 0) {
        return memorized_record[i][j];
    }
    if (i > 0 && mtx[i - 1][j] < mtx[i][j]) {
        result = max(result, recSearch(mtx, i - 1, j, memorized_record));
    }
    if (j > 0 && mtx[i][j - 1] < mtx[i][j]) {
        result = max(result, recSearch(mtx, i, j - 1, memorized_record));
    }
    if (i < n - 1 && mtx[i + 1][j] < mtx[i][j]) {
        result = max(result, recSearch(mtx, i + 1, j, memorized_record));
    }
    if (j < n - 1 && mtx[i][j + 1] < mtx[i][j]) {
        result = max(result, recSearch(mtx, i, j + 1, memorized_record));
    }
    memorized_record[i][j] = result + 1;
    return result + 1;
}

int longestConsecutiveDecreasingLength(vector<vector<int>> &mtx)
{
    int m = mtx.size();
    assert(m > 0);
    int n = mtx[0].size();
    assert(n > 0);
    vector<vector<int>> memorized_record(m, vector<int>(n, 0));
    int result = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result = max(result, recSearch(mtx, i, j, memorized_record));
        }
    }
    return result;
}

// Longest Palindromic Substring
string longestPalindrome(string s)
{
    if (s.empty()) {
        return "";
    }
    int n = s.size();
    int start = 0;
    int length = 1;
    bool flag[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            flag[i][j] = (i >= j);
        }
    }
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < j; i++) {
            flag[i][j] = (s[i] == s[j]) ? flag[i + 1][j - 1] : false;
            if (flag[i][j]) {
                if (j - i + 1 > length) {
                    length = j - i + 1;
                    start = i;
                }
            }
        }
    }
    return s.substr(start, length);
}

bool canJump(vector<int> &nums)
{
    int n = nums.size();
    if (n == 0) {
        return false;
    }
    std::vector<bool> can_jump(n, false);
    can_jump[n - 1] = true;
    for (int i = n - 2; i >= 0; i--) {
        int m = nums[i];
        for (int j = i + 1; j <= i + m && j < n; j++) {
            if (can_jump[j]) {
                can_jump[i] = true;
                break;
            }
        }
    }
    return can_jump[0];
}

int jump(vector<int> &nums)
{
    int n = nums.size();
    vector<int> dp(n, -1);
    dp[0] = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (j + nums[j] >= i) {
                dp[i] = (dp[i] == -1) ? dp[j] + 1 : min(dp[i], dp[j] + 1);
            }
        }
    }
    return dp[n - 1];
}

int uniquePaths(int m, int n)
{
    vector<int> result(n, 1);
    for (int i = 1; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result[j] += ((j == 0) ? 0 : result[j - 1]);
        }
    }
    return result[n - 1];
}

int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
{
    int m = obstacleGrid.size();
    if (m == 0) {
        return 0;
    }
    int n = obstacleGrid[0].size();
    if (n == 0) {
        return 0;
    }
    if (obstacleGrid[0][0] == 1) {
        return 0;
    }
    vector<int> result(n);
    result[0] = 1;
    for (int j = 1; j < n; j++) {
        result[j] = (obstacleGrid[0][j] == 1) ? 0 : result[j - 1];
    }
    for (int i = 0; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (obstacleGrid[i][j] == 1) {
                result[j] = 0;
            } else {
                result[j] += ((j == 0) ? 0 : result[j - 1]);
            }
        }
    }
    return result[n];
}

int minPathSum(vector<vector<int>> &grid)
{
    int m = grid.size();
    int n = grid[0].size();
    vector<int> result(n, 0);
    for (int i = 0; i < m; i++) {
        result[0] += grid[i][0];
        for (int j = 1; j < n; j++) {
            result[j] = grid[i][j] + ((i == 0) ? result[j - 1] : min(result[j - 1], result[j]));
        }
    }
    return result[n - 1];
}

int climbStairs(int n)
{
    vector<int> v(n + 2);
    v[1] = 1;
    v[2] = 2;
    for (int i = 3; i < n; i++) {
        v[i] = v[i - 1] + v[i - 2];
    }
    return v[n];
}

int minDistance(string word1, string word2)
{
    int m = word1.size();
    int n = word2.size();
    if (m == 0) {
        return n;
    }
    if (n == 0) {
        return m;
    }
    vector<vector<int>> dist(m + 1, vector<int>(n + 1));
    for (int i = 0; i < m + 1; i++) {
        dist[i][0] = i;
    }
    for (int j = 0; j < n + 1; j++) {
        dist[0][j] = j;
    }
    for (int i = 1; i < m + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            int update_cost = (word1[i] == word2[j]) ? 0 : 1;
            dist[i][j] = min(min(dist[i - 1][j] + 1, dist[i][j - 1] + 1),
                             dist[i - 1][j - 1] + update_cost);
        }
    }
    return dist[m][n];
}

int numDecodings(string s)
{
    if (s[0] <= '0' || s[0] > '9') {
        return 0;
    }
    int n = s.size();
    int dp[n + 1];
    dp[0] = dp[1] = 1;
    for (int i = 1; i < n; i++) {
        if ((s[i - 1] == '1') || (s[i - 1] == '2' && '0' <= s[i] && s[i] <= '6')) {
            dp[i] = dp[i - 2] + (s[i] == '0' ? 0 : dp[i - 1]);
        } else if ('0' < s[i] && s[i] <= '9') {
            dp[i] = dp[i - 1];
        } else {
            return 0;
        }
    }
    return dp[n];
}

bool isInterleave(string s1, string s2, string s3)
{
    int m = s1.size();
    int n = s2.size();
    if (s3.size() != m + n) {
        return false;
    }
    bool dp[m + 1][n + 1];
    dp[0][0] = true;
    for (int i = 1; i < m + 1; i++) {
        dp[i][0] = dp[i - 1][0] && (s1[i - 1] == s3[i - 1]);
    }
    for (int j = 1; j < n + 1; j++) {
        dp[0][j] = dp[0][j - 1] && (s2[j - 1] == s3[j - 1]);
    }
    for (int i = 1; i < m + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            dp[i][j] = (dp[i - 1][j] && (s1[i - 1] == s3[i + j - 1])) || (dp[i][j - 1] && (s2[j - 1] == s3[i + j - 1]));
        }
    }
    return dp[m][n];
}

int numDistinct(string s, string t)
{
    int m = t.size();
    int n = s.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    dp[0].assign(n, 1);
    for (int i = 0; i < m; i++) {
        for (int j = i; j < n; j++) {
            dp[i + 1][j + 1] = dp[i + 1][j] + ((t[i] == s[j]) ? dp[i][j] : 0);
        }
    }
    return dp[m][n];
}

int minimumTotal(vector<vector<int>> &triangle)
{
    int m = triangle.size();
    if (m == 0) {
        return 0;
    }
    vector<vector<int>> sum = triangle;
    for (int i = m - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            sum[i][j] += min(sum[i + 1][j], sum[i + 1][j + 1]);
        }
    }
    return sum[0][0];
}

vector<vector<string>> partition(string s)
{
    int n = s.size();
    vector<vector<bool>> flag(n, vector<bool>(n, true));
    for (int j = 0; j < n; j++) {
        flag[j][j] = true;
        for (int i = j - 1; i >= 0; i--) {
            flag[i][j] = (s[j] == s[i] && flag[i + 1][j - 1]);
        }
    }
    vector<vector<string>> result;
    vector<vector<vector<string>>> dp(n + 1);
    dp[0] = {{}};
    dp[1] = {{s.substr(0, 1)}};
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (flag[j][i]) {
                for (vector<string> u: dp[j]) {
                    u.push_back(s.substr(j, i - j + 1));
                    dp[i + 1].push_back(u);
                }
            }
        }
    }
    return dp[n];
}

int minCut(string s)
{
    int n = s.size();
    vector<vector<bool>> flag(n, vector<bool>(n, true));
    for (int j = 0; j < n; j++) {
        flag[j][j] = true;
        for (int i = j - 1; i >= 0; i--) {
            flag[i][j] = (s[j] == s[i] && flag[i + 1][j - 1]);
        }
    }
    vector<int> dp(n + 1, n);
    dp[0] = -1;
    dp[1] = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (flag[j][i]) {
                dp[i + 1] = min(dp[i + 1], dp[j] + 1);
                if (dp[i + 1] == 0) {
                    break;
                }
            }
        }
    }
    return dp[n];
}

int main()
{
    cout << minCut("aabcbcd") << endl;
    vector<int> a = {1,2,3,5,6,7,8};
    auto itr = lower_bound(a.begin(),a.end(),1);
    cout << itr - a.begin() << endl;
    return 0;
}

