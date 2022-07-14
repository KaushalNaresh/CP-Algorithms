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
    
    /*
        Method 1 : Using inorder recursion and struct to store maximum, minimum of left and right subtree and bool value if its a BST
        Time Complexity : O(H) where H is the height of a tree
        Space Complexity : O(H) because of calling stack
    */
    struct payload{
        bool isBST;
        TreeNode* max;
        TreeNode* min;
        
        payload(bool isBST, TreeNode* max, TreeNode* min){
            this->isBST = isBST;
            this->max = max;
            this->min = min;
        }
    };
    
    payload* isValidBSTUtil(TreeNode* root){
        
        if(root == nullptr)
            return new payload(true, nullptr, nullptr);
        
        payload* leftSub = isValidBSTUtil(root->left);
        payload* rightSub = isValidBSTUtil(root->right);
        bool isRootBST = true;
        
        if(leftSub->max != nullptr && root->val <= leftSub->max->val)
            isRootBST = false;
        
        if(rightSub->max != nullptr && root->val >= rightSub->min->val)
            isRootBST = false;
           
        int currMax = rightSub->max == nullptr ? root->val : rightSub->max->val;
        int currMin = leftSub->min == nullptr ? root->val : leftSub->min->val;
        int currIsBST = leftSub->isBST && rightSub->isBST && isRootBST;
        
        payload* res = new payload(currIsBST, new TreeNode(currMax), new TreeNode(currMin));
        
        return res;
    }
    
    bool isValidBST(TreeNode* root) {
        
        payload* ans = isValidBSTUtil(root);
        
        return ans->isBST;
    }
    
    /*
        Method 2 : Using stack we will traverse the tree in inorder fashion and check if numbers are in increasing order
        Time Complexity : O(H) where H is height of tree
        Space Complexity : O(H)
    */
    
    bool isValidBST(TreeNode* root) {
        
        vector<TreeNode*> stack;
        TreeNode *curr = root, *prev = nullptr;
        
        while(!stack.empty() || curr != nullptr){
            if(curr != nullptr){
                stack.push_back(curr);
                curr = curr->left;
            }
            else{
                curr = stack.back();
                stack.pop_back();
                if(prev != nullptr && curr->val <= prev->val)
                    return false;
                prev = curr;
                curr = curr->right;
            }
        }
        
        return true;
    }
    
    /*
        Method 3 : Using inorder recursion without using any struct
        Time Complexity : O(H) where H is height of tree
        Space Complexity : O(H)
    */
    
    bool isValidBST(TreeNode* root) {
        return isValidBST(root, NULL, NULL);
    }

    bool isValidBST(TreeNode* root, TreeNode* minNode, TreeNode* maxNode) {
        if(!root) return true;
        if(minNode && root->val <= minNode->val || maxNode && root->val >= maxNode->val)
            return false;
        return isValidBST(root->left, minNode, root) && isValidBST(root->right, root, maxNode);
    }
};
