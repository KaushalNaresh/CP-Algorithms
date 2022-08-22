#include<bits/stdc++.h>
using namespace std;

void add(int n, int idx, deque<pair<int, int>>& dq){

    while(!dq.empty() && dq.front().second <= n){
        dq.pop_back();
    }
    dq.push_back({idx, n});
}

void remove(deque<pair<int, int>>& dq, int idx){

    if(dq.front().first == idx)
        dq.pop_front();
}

vector<int> windowMax(vector<int> nums, int k){

    int n = nums.size();
    deque<pair<int, int>> dq;
    vector<int> ans;

    for(int i = 0; i < n; i++){
        if(i >= 3){
            ans.push_back(dq.front().second);
            remove(dq, i);
        }
        add(nums[i], i, dq);
    }

    ans.push_back(dq.front().second);

    return ans;

}

int main(){

    vector<int> nums;
    int n, k, num;

    cin>>n>>k;

    for(int i = 0; i < n; i++){
        cin>>num;
        nums.push_back(num);
    }

    vector<int> ans = windowMax(nums, k);

    for(auto i : ans)
        cout<<i<<" ";
    cout<<endl;

}