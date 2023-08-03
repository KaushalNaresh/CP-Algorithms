#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    int utilFunc(vector<int> &new_cuts, vector<vector<int>> &dp, int i, int j){

        if(j-i == 1)
            return 0;

        if(dp[i][j] != INT_MAX)
            return dp[i][j];

        for(int x = i+1; x < j; x++){
            dp[i][j] = min(dp[i][j], utilFunc(new_cuts, dp, i, x) + utilFunc(new_cuts, dp, x, j) +
                                     new_cuts[j]-new_cuts[i]);
        }

        return dp[i][j];
    }

    int minCost(int n, vector<int>& cuts) {
        
        sort(cuts.begin(), cuts.end());

        vector<int> new_cuts = {0};
        for(int i = 0; i < cuts.size(); i++)
            new_cuts.push_back(cuts[i]);
        new_cuts.push_back(n);

        int size = new_cuts.size();

        vector<vector<int>> dp(size, vector<int>(size, INT_MAX));

        return utilFunc(new_cuts, dp, 0, size-1);
    }
};