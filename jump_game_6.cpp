#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        
        int n = nums.size();
        deque<int> dq;
        dq.push_back(0);
        vector<int> dp(n);
        dp[0] = nums[0];
        
        for(int i = 1; i < n; i++){
            dp[i] = nums[i] + dp[dq.front()];
            
            while(!dq.empty() && dp[dq.back()] <= dp[i])
                dq.pop_back();
            
            dq.push_back(i);
            
            if(i-dq.front() >= k)
                dq.pop_front();
        }
        
        return dp[n-1];
        
    }
};