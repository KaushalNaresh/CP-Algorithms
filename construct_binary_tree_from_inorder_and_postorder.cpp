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

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder, int in_l, int in_r, int post_l, int post_r) {

        if(in_l > in_r || post_l > post_r)
            return NULL;
        
        if(in_l == in_r || post_l == post_r)
            return new TreeNode(inorder[in_l]);

        int idx = -1;

        TreeNode* root = new TreeNode(postorder[post_r]);

        for(int i = in_l; i <= in_r; i++){
            if(inorder[i] == root->val){
                idx = i;
                break;
            }
        }

        TreeNode* left = buildTree(inorder, postorder, in_l, idx-1, post_l, post_l+idx-1-in_l);
        TreeNode* right = buildTree(inorder, postorder, idx+1, in_r, post_l+idx-1-in_l+1, post_r-1);

        root->left = left;
        root->right = right;

        return root;
    }


    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        
        int n = inorder.size();

        return buildTree(inorder, postorder, 0, n-1, 0, n-1);
    }
};

/*

        9
    8       0
1          4. 5

inorder = 1 8 9 4 0 5
postorder = 1 8 4 5 0 9

        left = func(inorder(0:2), postorder(0:1))
        right = func(inorder(3:), postorder(2:5))

        rec = 1
        inorder = 1 8 9 4 0 5
        postorder = 1 8 4 5 0 9

        left = func(inorder(0:2), postorder(0:1))
        right = func(inorder(3:), postorder(2:5))

        9
    8           0
1.    null    4.   5

        rec=2

        lef -> inorder = 1, 8
               postorder = 1, 8

               left = func(inorder(0:0), postorder(0:0)) = 1
               right = func(inorder(2:), postorder(2:2)) = null

               8
            1      null

            
        right ->inorder = 4, 0, 5
                postorder = 4, 5, 0

                left = func(inorder(0:0), postorder(0:0)). 4
                right = func(inorder(2:2), postorder(1:1)). 5

                0
            4       5


*/