#include "common.h"

int maxSumSearch(TreeNode *node, int &globalMax)
{
    if (node == nullptr) {
        return 0;
    }
    int lmax = node->left ? maxSumSearch(node->left, globalMax) : 0;
    int rmax = node->right ? maxSumSearch(node->right, globalMax) : 0;
    globalMax = std::max(globalMax, node->val + std::max(lmax, 0) + std::max(rmax, 0));
    return std::max(node->val, std::max(node->val + lmax, node->val + rmax));
}

int maxPathSum(TreeNode *root)
{
    if (root == nullptr) {
        return -1;
    }
    int result = root->val;
    maxSumSearch(root, result);
    return result;
}

int height(TreeNode* node)
{
    if (node == nullptr){
        return 0;
    }
    int hl = node->left?height(node->left):0;
    if (hl == -1){
        return -1;
    }
    int hr = node->right?height(node->right):0;
    if (hr == -1){
        return -1;
    }
    if (abs(hr-hl) > 1){
        return -1;
    }else {
        return max(hr,hl) + 1;
    }
}

bool isBalanced(TreeNode* root)
{
    return height(root) != -1;
}