#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countSubstrings(string s) {
        
        int n = s.size();
        vector<vector<pair<bool,int>>> dp(n, vector<pair<bool,int>>(n, {false,0}));
        
        for(int i = 0; i < n; i++)
            dp[i][i] = {true, 1};
        
        for(int i = 2; i <= n; i++){
            for(int j = 0; j <= n-i; j++){
                int endIdx = j+i-1;
                
                if(i == 2)
                    dp[j][endIdx] = s[j] == s[endIdx] ? 
                                    pair<bool,int>{true, 3} :
                                    pair<bool,int>{false, 2};
                else                                                        
                    dp[j][endIdx] = s[j] == s[endIdx] && 
                                    dp[j+1][endIdx-1].first ? 
                                    pair<bool,int>{true, 1+dp[j][endIdx-1].second+
                                                           dp[j+1][endIdx].second-
                                                           dp[j+1][endIdx-1].second} :
                                    pair<bool,int>{false, dp[j][endIdx-1].second+
                                                          dp[j+1][endIdx].second-
                                                          dp[j+1][endIdx-1].second};
            }
        }
        
        return dp[0][n-1].second;
    }
};