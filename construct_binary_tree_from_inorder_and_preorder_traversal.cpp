#include<bits/stdc++.h>
using namespace std;
/*Definition for a binary tree node.*/
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
    
    TreeNode* buildTreeUtil(vector<int>& preorder, unordered_map<int, int>& m, int LB, int UB, int &idx){
        
        if(LB > UB){
            idx -= 1;
            return nullptr;
        }
        if(LB == UB)
            return new TreeNode(preorder[idx]);
        
        int currRoot = m[preorder[idx]];
        TreeNode* node = new TreeNode(preorder[idx]);
        idx += 1;
        node->left = buildTreeUtil(preorder, m, LB, currRoot-1, idx);
        idx += 1;
        node->right = buildTreeUtil(preorder, m, currRoot+1, UB, idx);
        
        return node;
    }
    
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        
        unordered_map<int, int> m;
        
        for(int i = 0; i < inorder.size(); i++){
            m[inorder[i]] = i;
        }
        
        int idx = 0;
        return buildTreeUtil(preorder, m, 0, inorder.size()-1, idx);
    }
};