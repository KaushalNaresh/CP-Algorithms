#include<bits/stdc++.h>

using namespace std;

int main(){

    int n, m, numb, maxSoFar = INT_MIN;
    cin>>n;
    vector<int> numbers, queries, maxs(n), ans;
    
    for(int i = 0; i < n; i++){
        cin>>numb;
        numbers.push_back(numb);
    }

    cin>>m;
    for(int i = 0; i < m; i++){
        cin>>numb;
        queries.push_back(numb);
    }

    unordered_map<int, int> map;

    for(int i = n-1; i >= 0; i--){
        if(numbers[i] > maxSoFar){
            maxSoFar = numbers[i];
        }
        map[numbers[i]-1]++;
        maxs[i] = map[maxSoFar-1];
    }

    for(int i = 0; i < m; i++){
        ans.push_back(maxs[queries[i]-1]);
    }

    for(int i = 0; i < m; i++)
        cout<<ans[i]<<" ";

}