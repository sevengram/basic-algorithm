#include "common.h"

vector<vector<int>> levelOrder(TreeNode *root)
{
    if (root == nullptr) {
        return {};
    }
    queue<TreeNode *> q;
    q.push(root);
    vector<vector<int>> result;
    while (!q.empty()) {
        size_t n = q.size();
        vector<int> level;
        for (int i = 0; i < n; i++) {
            TreeNode *p = q.front();
            q.pop();
            level.push_back(p->val);
            if (p->left) {
                q.push(p->left);
            }
            if (p->right) {
                q.push(p->right);
            }
        }
        result.push_back(level);
    }
    return result;
}

vector<vector<int>> zigzagLevelOrder(TreeNode *root)
{
    if (root == nullptr) {
        return {};
    }
    vector<vector<int>> result;
    stack<TreeNode *> s[2];
    s[0].push(root);
    int ln = 0;
    while (!s[ln % 2].empty()) {
        vector<int> level;
        while (!s[ln % 2].empty()) {
            TreeNode *p = s[ln % 2].top();
            s[ln % 2].pop();
            level.push_back(p->val);
            if (ln % 2 == 0) {
                if (p->left) {
                    s[(ln + 1) % 2].push(p->left);
                }
                if (p->right) {
                    s[(ln + 1) % 2].push(p->right);
                }
            } else {
                if (p->right) {
                    s[(ln + 1) % 2].push(p->right);
                }
                if (p->left) {
                    s[(ln + 1) % 2].push(p->left);
                }
            }
        }
        result.push_back(level);
        ln++;
    }
    return result;
}

void recTraversal(TreeNode *n, vector<int> &result)
{
    if (n == nullptr) {
        return;
    }
    if (n->left) {
        recTraversal(n->left, result);
    }
    result.push_back(n->val);
    if (n->right) {
        recTraversal(n->right, result);
    }
}

vector<int> inorderTraversal(TreeNode *root)
{
    vector<int> result;
    recTraversal(root, result);
    return result;
}


