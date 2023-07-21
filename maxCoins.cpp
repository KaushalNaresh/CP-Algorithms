#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    int maxCoins(vector<int> Nums) {
        int nums[Nums.size() + 2];
        int n = Nums.size();
        for(int i = 0; i < Nums.size(); i++)
            nums[i+1] = Nums[i];
        nums[0] = nums[n+1] = 1;

        n = n+2;


        vector<vector<int>> dp(n, vector<int>(n, 0));
        for(int k = 2; k < n; k++) {
            for(int left = 0; left < n - k; left++){
                int right = left + k;
                for(int i = left + 1; i < right; ++i)
                    dp[left][right] = max(dp[left][right],
                        nums[left] * nums[i] * nums[right] + dp[left][i] + dp[i][right]);
            }
        }

        return dp[0][n - 1];
    }
};