#include<bits/stdc++.h>
using namespace std;

class node{
    public:

    node *left, *right;
    int data;
    node(int n){
        left = NULL;
        right = NULL;
        data = n;
    }
};


int main(){

    stack<node*> st;
    node* root = new node(0);
    st.push(root);

    /* Without affecting the original tree inorder traversal*/
    node* curr = root;
    while(!st.empty()){
        
        if(curr != NULL){
            st.push(curr);
            curr = curr->left;
        }
        else{
            curr = st.top();
            cout<<curr->data;
            st.pop();
            curr=curr->right; 
        }
    }

    /*Now for preorder*/
    node* curr = root;
    while(!st.empty()){

        if(curr != NULL){
            cout<<curr;
            st.push(curr);
            curr = curr->left;
        }
        else{
            curr = st.top();
            st.pop();
            curr = curr->right;
        }

    }

    /*Now for postorder*/

    node *curr = root, *temp;
    while(!st.empty()){

        if(curr != NULL){
            if(curr->right){
                st.push(curr->right);
            }
            st.push(curr);
            curr = curr->left;
        }
        else{
            curr = st.top();
            st.pop();
            if(curr->right && st.top() == curr->right){
                temp = st.top();
                st.pop();
                st.push(curr);
                curr = temp;
            }
            else{
                cout<<curr->data;
                curr = NULL;
            }
        }
    }

    // Post Order using 2 stacks
    vector<node*> stack1;
    vector<node*> stack2;

    if(root == NULL)
        return;

    stack1.push_back(root);

    while(!stack1.empty()){

        node* topNode = stack1.back();
        stack2.push_back(topNode);
        stack1.pop_back();

        if(topNode->left != NULL)
            stack1.push_back(topNode->left);
        
        if(topNode->right != NULL)
            stack1.push_back(topNode->right);
    } 

    for(int i = stack2.size()-1; i >= 0; i--){
        cout<<stack2[i]<<" ";
    }

}