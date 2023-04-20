/*
Given an integer n, break it into the sum of k positive integers, 
where k >= 2, and maximize the product of those integers.
Return the maximum product you can get.
*/

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int integerBreak(int n) {
        
        vector<int> dp(n, 1);
        int ans = INT_MIN;

        for(int i = 0; i < n-1; i++)
            dp[i] = i+1;

        for(int i = 2; i <= n; i++){
            for(int j = 2; j < i; j++){
                
                int prod = (i-j)*dp[j-1];

                if(prod > dp[i-1])
                    dp[i-1] = prod;
            }
        }

        return dp[n-1];
    }
};

int main(){

    int n;
    Solution* soln = new Solution();
    cin>>n;
    soln->integerBreak(n);
}