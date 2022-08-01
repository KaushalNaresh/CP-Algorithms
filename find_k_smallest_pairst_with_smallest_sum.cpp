/*
    Several solutions from naive to more elaborate. I found it helpful to visualize the input as an m×n matrix of sums, 
    for example for nums1=[1,7,11], and nums2=[2,4,6]:
          2   4   6
        +------------
     1 |  3   5   7
     7 |  9  11  13
    11 | 13  15  17

    Of course the smallest pair overall is in the top left corner, the one with sum 3. We don't even need to look anywhere else. 
    After including that pair in the output, the next-smaller pair must be the next on the right (sum=5) or the next below (sum=9). 
    We can keep a "horizon" of possible candidates, implemented as a heap / priority-queue, and roughly speaking we'll grow from
    the top left corner towards the right/bottom.

    # # # # # ? . .
    # # # ? ? . . .
    # ? . . . . . .   "#" means pair already in the output
    # ? . . . . . .   "?" means pair currently in the queue
    # ? . . . . . .
    ? . . . . . . .
    . . . . . . . .
*/


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