#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        
        int n = strs.size(), m = strs[0].size(), res = 0, j;
        vector<bool> sorted(m, false);

        for(int i = 0; i < m; i++){
            for(j = 0; j < n-1; j++){
                if(!sorted[j] && strs[j][i] > strs[j+1][i]){
                    res++;
                    break;
                }
            }

            if(j < n-1)
                continue;
            for(j = 0; j < n-1; j++)
                sorted[j] = sorted[j] || strs[j][i] < strs[j+1][i];
        }

        return res;
    }
};