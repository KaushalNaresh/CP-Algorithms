/*
    This is a version of standard digit dp problem
*/

#include<bits/stdc++.h>
using namespace std;

vector<vector<vector<int>>> dp;

class Solution {
public:

    int digitDP(string &s, int pos = 0, int tight = 1, int mask = 0){

        if(pos == s.size())
            return mask != 0;

        if(dp[pos][tight][mask] != -1)
            return dp[pos][tight][mask];

        int ans = 0;
        
        if(tight == 1){
            for(int i = 0; i <= s[pos]-'0'; i++){
                if(mask & (1 << i))
                    continue;

                int newMask = (mask == 0 && i == 0) ? mask : (mask | (1 << i));
                if(i == s[pos]-'0')
                    ans += digitDP(s, pos+1, 1, newMask);
                else
                    ans += digitDP(s, pos+1, 0, newMask);
            }
        }
        else{
            for(int i = 0; i <= 9; i++){
                if(mask & (1 << i))
                    continue;

                int newMask = (mask == 0 && i == 0) ? mask : (mask | (1 << i));
                ans += digitDP(s, pos+1, 0, newMask);
            }
        }

        return dp[pos][tight][mask] = ans;
    }

    int countSpecialNumbers(int n) {
        
        dp = vector<vector<vector<int>>>(10, vector<vector<int>>(2, vector<int>(1024, -1)));
        string s = to_string(n);
        return digitDP(s);
    }
};

int main(){

    Solution* sol = new Solution();
    int n;
    cin>>n;
    cout<<sol->countSpecialNumbers(n);
}