#include<bits/stdc++.h>
using namespace std;

struct Node {
    struct Node* left, *right;
    int key;
};
 
struct Node* newNode(int key)
{
    struct Node* ptr = new Node;
    ptr->key = key;
    ptr->left = ptr->right = NULL;
    return ptr;
}
 
// Standard BST insert function
struct Node* insert(struct Node* root, int key)
{
    if (!root)
        root = newNode(key);
    else if (root->key > key)
        root->left = insert(root->left, key);
    else if (root->key < key)
        root->right = insert(root->right, key);
    return root;
}

// LCA 
Node* LCA(Node* root, int a, int b){

    while((root->key-a)*(root->key-b) > 0){
        root = root->key > a ? root->left : root->right;
    }

    return root;
}

int dist(Node* root, int idx){

    if(root == NULL)
        return 0;

    if(root->key == idx)
        return 1;

    else if(root->key < idx)
        return 1+dist(root->right, idx);
    else
        return 1+dist(root->left, idx);
    
}

int main(){

    struct Node* root = NULL;
    root = insert(root, 20);
    insert(root, 10);
    insert(root, 5);
    insert(root, 15);
    insert(root, 30);
    insert(root, 25);
    insert(root, 35);
    int a = 5, b = 10;
    Node* node = LCA(root, a, b);
    int dist1 = dist(node, a);
    int dist2 = dist(node, b);
    int ans = dist1-1 + dist2-1 - 1;
    cout<<ans;
    return 0;
}