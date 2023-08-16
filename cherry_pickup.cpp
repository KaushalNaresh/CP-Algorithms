#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    vector<vector<int>> grid;
    vector<vector<vector<int>>> dp;
    int N;

    int cherryPickup(vector<vector<int>>& grid) {

        this->grid = grid;
        this->N = grid.size();

        dp = vector<vector<vector<int>>>(N, vector<vector<int>>(N, vector<int>(N, INT_MIN)));

        return max(0, utilFunc(0, 0, 0)); // r1 = 0, c1 = 0, r2 = 0
    }

    int utilFunc(int r1, int c1, int c2){

        int r2 = r1+c1-c2;

        if(r1 == N || c1 == N || r2 == N || c2 == N || grid[r1][c1] == -1 || grid[r2][c2] == -1)
            return INT_MIN;

        if(r1 == N-1 && c1 == N-1)
            return grid[r1][c1];

        if(dp[r1][c1][c2] != INT_MIN)
            return dp[r1][c1][c2];

        int ans = grid[r1][c1];
        if(c1 != c2)
            ans += grid[r2][c2];

        ans += max(max(utilFunc(r1+1, c1, c2), utilFunc(r1, c1+1, c2)),
                   max(utilFunc(r1+1, c1, c2+1), utilFunc(r1, c1+1, c2+1)));

        dp[r1][c1][c2] = ans;
        return ans;

    }

};