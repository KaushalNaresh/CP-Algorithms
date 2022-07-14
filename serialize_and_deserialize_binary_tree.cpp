#include<bits/stdc++.h>
using namespace std;

/* Definition for a binary tree node.*/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
public:

    // Encodes a tree to a single string.
    // We will use Pre Order Traversal for encoding
    string serialize(TreeNode* root) {
        
        if(root == nullptr)
            return "";
        
        string ser = "";
        vector<TreeNode*> stack;
        TreeNode* curr = root;
        stack.push_back(curr);
        
        while(!stack.empty()){
            
            if(curr != nullptr){
                stack.push_back(curr);
                ser += to_string(curr->val)+" ";
                curr = curr->left;
            }
            else{
                ser += "X ";
                curr = stack.back();
                stack.pop_back();
                curr = curr->right;
            }
        }
        
        return ser;
    }
    
    // traverse the string serially and X will tell us where to terminate the subtree
    TreeNode* deserializeUtil(deque<string>& values){
        
        if(values.size() == 0)
            return nullptr;
        string value = values.front();
        values.pop_front();
        
        if(value == "X")
            return nullptr;
            
        TreeNode* node = new TreeNode(stoi(value));
        node->left = deserializeUtil(values);
        node->right = deserializeUtil(values);
        
        return node;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        
        stringstream ss(data);
        deque<string> values;
        string str;
        while(ss>>str){
            values.push_back(str);
        }    cout<<str<<" ";
        
        return deserializeUtil(values);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
