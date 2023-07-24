#include<bits/stdc++.h>
using namespace std;

int main(){

    string s, t;
    cin>>s>>t;

    int n_s = s.size(), n_t = t.size();
    
    vector<vector<int>> dp(n_s+1, vector<int>(n_t+1, 0));

    for(int i = 1; i <= n_s; i++){
        for(int j = 1; j <= n_t; j++){
            if(s[i-1] == t[j-1])
                dp[i][j] = dp[i-1][j-1]+1;
            else
                dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
        }
    }

    int i = n_s, j = n_t;
    string ans = "";
    while(i > 0 && j > 0){
        if(s[i-1] == t[j-1]){
            ans += s[i-1];
            i = i-1;
            j = j-1;
        }
        else{
            if(dp[i-1][j] > dp[i][j-1])
                i = i-1;
            else
                j = j-1;
        }
    }

    reverse(ans.begin(), ans.end());

    cout<<ans;
}