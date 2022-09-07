#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        
        deque<pair<int, int>> mindq, maxdq;
        int n = nums.size(), lptr = 0, max = INT_MIN;
        
        for(int i = 0; i < n; i++){
            while(!mindq.empty() && mindq.back().second > nums[i]) mindq.pop_back();
            while(!maxdq.empty() && maxdq.back().second < nums[i]) maxdq.pop_back();
            
            mindq.push_back({i, nums[i]});
            maxdq.push_back({i, nums[i]});
            
            while(maxdq.front().second - mindq.front().second > limit){
                if(lptr == maxdq.front().first) maxdq.pop_front();
                if(lptr == mindq.front().first) mindq.pop_front();
                lptr++;
            }
            if(max < (i-lptr+1))
                max = i-lptr+1;
        }
        
        return max;
    }
};