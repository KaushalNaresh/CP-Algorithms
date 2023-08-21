#include<bits/stdc++.h>
using namespace std;

/*
Definition for a binary tree node.*
*/

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

    unordered_map<int, vector<TreeNode*>> map;
    vector<TreeNode*> allPossibleFBT(int n) {

        if(n%2 == 0)
            return {};

        if(n == 1)
            return {new TreeNode(0)};

        if(map.find(n) != map.end())
            return map[n];

        vector<TreeNode*> ans;

        for(int i = 1; i < n; i+=2){
            vector<TreeNode*> leftTrees = allPossibleFBT(i);
            vector<TreeNode*> rightTrees = allPossibleFBT(n-(i+1));

            for(auto l : leftTrees){
                for(auto r : rightTrees){
                    TreeNode* root = new TreeNode(0);
                    root->left = l;
                    root->right = r;
                    ans.push_back(root);
                }
            }
        }

        return map[n] = ans;
    }
};