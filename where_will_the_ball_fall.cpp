#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findBall(vector<vector<int>>& grid) {
        
        int r = grid.size(), c = grid[0].size();
        vector<int> ans(c, -1);

        bool isStuck = false;

        for(int i = 0; i < c; i++){
            int k = i;
            isStuck = false;
            for(int j = 0; j < r; j++){
                if(grid[j][k] == 1){
                    if(k == c-1 || grid[j][k+1] == -1){
                        isStuck = true;
                        break;
                    }
                    else
                        k = k+1;
                }
                else{
                    if(k == 0 || grid[j][k-1] == 1){
                        isStuck = true;
                        break;
                    }
                    else
                        k = k-1;
                }
            }

            if(!isStuck && k >= 0  && k < c)
                ans[i] = k;
        }

        return ans;
    }
};