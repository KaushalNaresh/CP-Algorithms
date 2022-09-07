#include<bits/stdc++.h>
using namespace std;

int main(){

    int n, k, num;
    cin>>n>>k;
    vector<int> vec;
    for(int i = 0; i < n; i++){
        cin>>num;
        vec.push_back(num);
    }

    deque<int> maxdq, mindq;
    int lptr = 0, ans = 0;

    for(int i = 0; i < n; i++){

        while(!maxdq.empty() && maxdq.back() < vec[i]) maxdq.pop_back();
        while(!mindq.empty() && mindq.back() > vec[i]) maxdq.pop_back();

        maxdq.push_back(vec[i]);
        mindq.push_back(vec[i]);

        while(!maxdq.empty() && !mindq.empty() && 
              maxdq.front() - mindq.front() > k){
            if(vec[lptr] == maxdq.front()) maxdq.pop_front();
            if(vec[lptr] == mindq.front()) mindq.pop_front();
            lptr++;
        }
        ans += i-lptr+1;
    }

    cout<<ans<<endl;
}