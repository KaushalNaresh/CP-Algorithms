#include<bits/stdc++.h>

using namespace std;

class Node {
    public:
        int data;
        Node *left;
        Node *right;
        Node(int d) {
            data = d;
            left = NULL;
            right = NULL;
        }
};

class Solution {
    public:
  		Node* insert(Node* root, int data) {
            if(root == NULL) {
                return new Node(data);
            } else {
                Node* cur;
                if(data <= root->data) {
                    cur = insert(root->left, data);
                    root->left = cur;
                } else {
                    cur = insert(root->right, data);
                    root->right = cur;
               }

               return root;
           }
        }

    void topView(Node * root) {
        
        unordered_map<int, int> m;
        queue<pair<int, Node*>> q;
        int start = INT_MAX;
        
        q.push({0, root});
        
        while(!q.empty()){
            
            int n = q.size();
            
            for(int i = 0; i < n; i++){
                pair<int, Node*> p = q.front();
                int idx = p.first;
                Node* node = p.second;
                
                q.pop();
                
                if(!m.count(idx)){
                    if(start > idx)
                        start = idx;
                    m[idx] = node->data;    
                }
                
                if(node->left)
                    q.push({idx-1,node->left});
                if(node->right)
                    q.push({idx+1, node->right});
            }
        }
        
        int n = m.size();
        vector<int> ans(n);
        
        for(auto itr = m.begin(); itr != m.end(); itr++){
            ans[itr->first+abs(start)] = itr->second;
        }
        
        for(int i = 0; i < ans.size(); i++){
            cout<<ans[i]<<" ";
        }
    }

}; //End of Solution