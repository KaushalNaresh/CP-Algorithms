#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int removeBoxes(vector<int>& boxes) {
        
        // [1,3,2,2,2,3,4,3,1]
        int n = boxes.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n, 0)));

        for(int i = 0; i < n; i++){
            for(int k = 0; k <= i; k++){
                dp[i][i][k] = (k+1)*(k+1);
            }
        }

        for(int l = 1; l <= n; l++){
            for(int j = l; j < n; j++){
                int i = j-l;
                for(int k = 0; k <= i; k++){
                    dp[i][j][k] = (k+1)*(k+1) + dp[i+1][j][0];
                    for(int m = i+1; m <= j; m++){
                        if(boxes[m] == boxes[i])
                            dp[i][j][k] = max(dp[i][j][k], dp[i+1][m-1][0]+dp[m][j][k+1]);
                    }
                }
            }
        }

        return dp[0][n-1][0];
    }
};