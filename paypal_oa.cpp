#include<bits/stdc++.h>
using namespace std;

class Node{

    public:
    int val, l, r;
    Node* left, *right;
    Node(int val, int l, int r){
        this->val = val;
        this->l = l;
        this->r = r;
        left = nullptr;
        right = nullptr;
    }
};

Node* constructTree(vector<string> &arr, int LB, int UB){

    if(LB == UB){
        int n = arr[LB].size();

        if((arr[LB][0] == 'a' || arr[LB][0] == 'e' || arr[LB][0] == 'i' || 
           arr[LB][0] == 'o' || arr[LB][0] == 'u') &&
           (arr[LB][n-1] == 'a' || arr[LB][n-1] == 'e' || arr[LB][n-1] == 'i' || 
           arr[LB][n-1] == 'o' || arr[LB][n-1] == 'u')){

            return new Node(1, LB, UB);
        }
        else
            return new Node(0, LB, UB);
    }

    int mid = (LB+UB)/2;

    Node* left = constructTree(arr, LB, mid);
    Node* right = constructTree(arr, mid+1, UB);

    Node* node = new Node(left->val + right->val, LB, UB);
    node->left = left;
    node->right = right;

    return node;
}

int calcSum(Node* node, int l, int r){

    if(node == nullptr)
        return 0;

    if(node->l >= l && node->r <= r)
        return node->val;
    
    int mid = (node->l + node->r)/2;

    if(r < mid)
        return calcSum(node->left, l, r);
    else if(l > mid)
        return calcSum(node->right, l, r);
    else
        return calcSum(node->left, l, r) + calcSum(node->right, l, r);
}

void inorder(Node* root){

    if(root == nullptr)
        return;
    inorder(root->left);
    cout<<"("<<root->val<<","<<root->l<<","<<root->r<<")"<<" ";
    inorder(root->right);
}

vector<int> hasVowel(vector<string> strArr, vector<string> query){

    int n = strArr.size();
    Node* root = constructTree(strArr, 0, n-1);
    vector<int> ans;

    // inorder(root);
    // cout<<endl;

    for(int i = 0; i < query.size(); i++){
        string q = query[i];
        int del;
        for(int j = 0; j < q.size(); j++){
            if(q[j] == '-'){
                del = j;
                break;
            }
        }

        int n1 = stoi(q.substr(0, del));
        int n2 = stoi(q.substr(del+1, q.size()-del+1));

        int n = calcSum(root, n1-1, n2-1);
        ans.push_back(n);
    }

    return ans;

}


int main(){

    vector<string> strArr, query;
    int n, q;
    string str;

    cin>>n;
    for(int i = 0; i < n; i++){
        cin>>str;
        strArr.push_back(str);
    }

    cin>>q;
    for(int i = 0; i < q; i++){
        cin>>str;
        query.push_back(str);
    }

    vector<int> ans = hasVowel(strArr, query);

    for(auto i : ans)
        cout<<i<<" ";
}