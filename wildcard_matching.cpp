#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        
        int n_s = s.size(), n_p = p.size();
        vector<vector<int>> dp(n_s+1, vector<int>(n_p+1, false));

        dp[0][0] = true;

        for(int i = 1; i <= n_p; i++){
            if(p[i-1] == '*' && dp[0][i-1])
                dp[0][i] = true;
        }

        for(int i = 1; i <= n_s; i++){
            for(int j = 1; j <= n_p; j++){
                if((s[i-1] == p[j-1] || p[j-1] == '?') && dp[i-1][j-1])
                    dp[i][j] = true;
                else if(p[j-1] == '*')
                    dp[i][j] = dp[i-1][j] | dp[i][j-1];
            }
        }

        return dp[n_s][n_p];
    }
};