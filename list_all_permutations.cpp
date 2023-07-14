#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> perms;

void dfs(vector<int> &vec, int idx, vector<int> curr, vector<int> visited){

    if(curr.size() == vec.size()){
        perms.push_back(curr);
        return;
    }

    visited[idx] = 1;

    int n = vec.size();
    for(int i = 0; i < n; i++){
        if(visited[i] != 1){
            curr.push_back(vec[i]);
            dfs(vec, i, curr, visited);
            curr.pop_back();
        }
    }

    return;
}

int main(){

    vector<int> vec;
    int n, numb;

    cin>>n;

    for(int i = 0; i < n; i++){
        cin>>numb;
        vec.push_back(numb);
    }

    for(int i = 0; i < n; i++){
        vector<int> curr, visited(n, 0);
        curr.push_back(vec[i]);
        dfs(vec, i, curr, visited);
        curr.pop_back();
    }

    cout<<perms.size()<<endl;
}