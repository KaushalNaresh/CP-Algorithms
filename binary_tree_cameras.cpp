#include<bits/stdc++.h>
using namespace std;

/**
 * Definition for a binary tree node.*
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
    int ans = 0;
    int dfs(TreeNode* root){
        if(!root)
            return 0; // not needed
        int left = dfs(root->left);
        int right = dfs(root->right);

        if(left == 1 || right == 1){
            ans ++;
            return 2; // has camera
        }
        else if(left == 2 || right == 2)
            return 0;  // no camera
        else
            return 1; // no camera
    }

    int minCameraCover(TreeNode* root) {
        if(dfs(root) == 1) ans++;
        return ans;
    }
};