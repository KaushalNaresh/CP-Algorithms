/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:

    /*
        Method 1 : Using recursion and keeping track of whether p and q are visited
        Time Complexity : O(N) where N is number of nodes in a tree
        Space Complexity : O(H) where H is the height os a tree
    */
    
    pair<int, TreeNode*> utilFunc(TreeNode* root, TreeNode* p, TreeNode* q){
        
        if(root == nullptr)
            return {0, nullptr};
        
        pair<int, TreeNode*> ls = utilFunc(root->left, p, q);
        pair<int, TreeNode*> rs = utilFunc(root->right, p, q);
        
        if(ls.first == 2 || rs.first == 2) // If already ancestor is found
            return ls.first == 2 ? pair<int, TreeNode*>{2, ls.second} : pair<int, TreeNode*>{2, rs.second};
        
        int k = ls.first+rs.first;
        TreeNode* parentNode = nullptr;
        if(root->val == p->val || root->val == q->val)
            k += 1;
        
        return k != 2 ? pair<int, TreeNode*>{k, nullptr} : pair<int, TreeNode*>{k, root};
        
    }
    
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        
        return utilFunc(root, p, q).second;
    }
    
    /*
        Method 2 : Using recursion and BST properties
        Time Complexity : O(N) where N is the number of nodes in a tree
        Space somplexity : O(1)
    */

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        
        while((root->val-p->val) * (root->val-q->val) > 0)
            root = p->val > root->val ? root->right : root->left;
        
        return root;
    }

     /*
        Method 3 : Using recursion
        Time Complexity : O(N) where N is the number of nodes in a tree
        Space somplexity : O(N)
    */

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

        if (!root || root == p || root == q) return root;
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        return !left ? right : !right ? left : root;

    }
};