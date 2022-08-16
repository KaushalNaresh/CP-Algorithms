#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
    int total, start, end;
    Node* left, *right;
    
    Node(int start, int end){
        this->start = start;
        this->end = end;
        this->total = 0;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class NumArray {
public:
    Node* root;
    
    Node* createTree(vector<int> &nums, int l, int r){
        
        if(l == r){
            Node* node = new Node(l, r);
            node->total = nums[l];
            node->left = nullptr;
            node->right = nullptr;
            return node;
        }
        
        int mid = (l+r)/2;
        
        Node* leftNode = createTree(nums, l, mid);
        Node* rightNode = createTree(nums, mid+1, r);
        
        Node* root = new Node(l, r);
        root->total = leftNode->total + rightNode->total;
        root->left = leftNode;
        root->right = rightNode;
        
        return root;
    }
    
    NumArray(vector<int>& nums) {
        
        int n = nums.size();
        root = createTree(nums, 0, n-1);
    }
    
    int updateVal(Node* node, int index, int val){
        
        if(node->start == node->end){
            node->total = val;
            return val;
        }
        
        int mid = (node->start+node->end)/2;
        
        if(index <= mid)
            updateVal(node->left, index, val);
        else
            updateVal(node->right, index, val);
        
        node->total = node->left->total + node->right->total;
        return node->total;
    }
    
    void update(int index, int val) {
        
        updateVal(this->root, index, val);
        
    }
    
    void print(Node* root){
        
        if(root == nullptr)
            return;
        print(root->left);
        cout<<root->total<<" ";
        print(root->right);
    }
    
    int getSumRange(Node* node, int l, int r){
        
        if(node->start == l && node->end == r)
            return node->total;
        
        int mid = (node->start+node->end)/2;
        int lTotal = 0, rTotal = 0;
        
        if(r <= mid)
            return getSumRange(node->left, l, r);
        else if(l > mid)
            return getSumRange(node->right, l, r);
        else
            return getSumRange(node->left, l, mid) + getSumRange(node->right, mid+1, r);
        
    }
    
    int sumRange(int left, int right) {
        
        return getSumRange(this->root, left, right);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */