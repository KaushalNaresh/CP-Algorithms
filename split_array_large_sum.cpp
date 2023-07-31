#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        
        int n = nums.size();
        vector<int> sum(n, 0);

        for(int i = 0; i < n; i++){
            if(i == 0){
                sum[i] = nums[i];
                continue;
            }
            sum[i] = nums[i] + sum[i-1];
        }

        vector<vector<int>> dp(k, vector<int>(n, INT_MAX));

        for(int i = 0; i < n; i++)
            dp[0][i] = sum[i];

        for(int i = 1; i < k; i++){
            for(int j = 0; j < n; j++){
                if(j >= i){
                    for(int m = j-1; m >= 0; m--){
                        dp[i][j] = min(dp[i][j], max(sum[j]-sum[m], dp[i-1][m]));
                    }
                }
            }
        }

        return dp[k-1][n-1];
    }
};