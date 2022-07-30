#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        
        priority_queue<pair<int,vector<int>>, vector<pair<int,vector<int>>>, greater<pair<int,vector<int>>>> pq;
        vector<vector<int>> ans;
        set<vector<int>> s;
        
        pq.push({nums1[0]+nums2[0], {0, 0}});
        s.insert({0,0});
        
        while(k && !pq.empty()){
            
            pair<int, vector<int>> p = pq.top();
            vector<int> vec = p.second;
            int idx1 = vec[0];
            int idx2 = vec[1];
            ans.push_back({nums1[idx1], nums2[idx2]});
            pq.pop();
            
            if(idx1+1 < nums1.size() && (s.find({idx1+1, idx2}) == s.end()) ){
                pq.push({nums1[idx1+1]+nums2[idx2], {idx1+1, idx2}});
                s.insert({idx1+1, idx2});
            }
            if(idx2+1 < nums2.size() && (s.find({idx1, idx2+1}) == s.end()) ){
                pq.push({nums1[idx1]+nums2[idx2+1], {idx1, idx2+1}});
                s.insert({idx1, idx2+1});
            }
            
            k--;
        }
        
        return ans;
        
    }
};