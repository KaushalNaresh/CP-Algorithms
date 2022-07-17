#include<bits/stdc++.h>
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int res = INT_MIN;
    
    int solve(TreeNode* root){
        
        if(root == nullptr)
             return 0;
        
        int leftSum = solve(root->left);
        int rightSum = solve(root->right);
        
        int temp = max(max(leftSum, rightSum)+root->val, root->val);
        
        int ans = max(temp, leftSum+rightSum+root->val);
        
        this->res = max(ans, this->res);
        
        return temp;
    }
    
    int maxPathSum(TreeNode* root) {
        solve(root);
        return this->res;
    }
};