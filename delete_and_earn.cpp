#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        
        int n = nums.size(), prev = -1, currSum = 0;
        sort(nums.begin(), nums.end());
        vector<int> dp;
        vector<pair<int, int>> sums;
        
        for(int i = 0; i < n; i++){
            if(prev != -1 && nums[prev] != nums[i]){
                sums.push_back({nums[prev], currSum});
                currSum = 0;
            }
            currSum+=nums[i];
            prev = i;
        }
        
        if(currSum != 0)
            sums.push_back({nums[prev], currSum});
        
        dp = vector<int>(sums.size()+1, 0);
        dp[1] = sums[0].second;
        
        for(int i = 2; i <= sums.size(); i++){
            dp[i] = sums[i-2].first+1 == sums[i-1].first 
                        ? max(dp[i-2]+sums[i-1].second, dp[i-1]) 
                        : max(dp[i-1]+sums[i-1].second, dp[i-1]);
        }
        
        return dp[sums.size()];
    }
};