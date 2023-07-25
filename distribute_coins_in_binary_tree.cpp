#include<bits/stdc++.h>
using namespace std;

/**
* Definition for a binary tree node.
* */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int moves = 0;

    int distrCoinsUtil(TreeNode* root){
        if(!root)
            return 0;

        int left = distrCoinsUtil(root->left);
        int right = distrCoinsUtil(root->right);

        int diff = root->val+left+right - 1; // coins need to take or give

        moves += abs(diff);

        return diff;
    }

    int distributeCoins(TreeNode* root) {
        distrCoinsUtil(root);
        return moves;
    }
};