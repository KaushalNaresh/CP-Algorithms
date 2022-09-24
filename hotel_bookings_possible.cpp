#include<bits/stdc++.h>
using namespace std;

static bool compare(pair<int, int> p1, pair<int, int> p2){
    
    if(p1.first == p2.first){
        return p1.second > p2.second;
    }
    return p1.first < p2.first;
}

bool hotel(vector<int> &arrive, vector<int> &depart, int K) {
    
    vector<pair<int, int>> vec;
    
    for(int i = 0; i < arrive.size(); i++){
        vec.push_back({arrive[i], 1});
        vec.push_back({depart[i], 0});
    }
    
    sort(vec.begin(), vec.end(), compare);
    
    int currMax = 0, maxSoFar = 0;
    
    for(int i = 0; i < vec.size(); i++){
        if(vec[i].second == 1){
            currMax++;
            maxSoFar = max(currMax, maxSoFar);
        }
        else{
            currMax--;
        }
        
        if(currMax > K)
            return false;
    }
    
    return true;
}
