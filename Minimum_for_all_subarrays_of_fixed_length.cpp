/*
Suppose we are given an array A of length N and a given M <= N. 
We have to find the minimum of each subarray of length M in this array
We have to solve this problem in linear time, i.e. O(n)
*/


#include<bits/stdc++.h>
using namespace std;

int addCount = 0, removeCount = 0;

void add(deque<pair<int, int>> &dq, int n){

    while(!dq.empty() && dq.back().first > n){
        dq.pop_back();
    }
    dq.push_back({n, addCount});
    addCount += 1;
}

void remove(deque<pair<int, int>> &dq){

    if(!dq.empty() && dq.front().second == removeCount){
        dq.pop_front();
    }
    removeCount += 1;
}

int getMinimum(deque<pair<int, int>> dq){

    return dq.front().first;
}

int main(){

    int N, M;
    cin>>N>>M;

    vector<int> A(N, 0), minimums;

    for(int i = 0; i < N; i++){
        cin>>A[i];
    }

    deque<pair<int, int>> dq;
    int size = 0;

    for(auto a : A){
        if(size < M){
            add(dq, a);
            size += 1;
        }
        else if(size == M){
            minimums.push_back(getMinimum(dq));
            remove(dq);
            size -= 1;
            add(dq, a);
            size += 1;
        }
    }

    minimums.push_back(getMinimum(dq));

    for(auto min : minimums){
        cout<<min<<" ";
    }

}