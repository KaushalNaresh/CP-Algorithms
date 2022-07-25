#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    static bool compare(vector<int>& vec1, vector<int>& vec2){
        return vec1[0] < vec2[0];
    }
    
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        
        int n = people.size();
        vector<vector<int>> ans(n);
        
        sort(people.begin(), people.end(), compare);
        
        for(int i = 0 ; i < n; i++){
            vector<int> currPerson = people[i];
            for(int j = 0; j < n; j++){
                if(currPerson[1] == 0){
                    if(ans[j].size() != 0)
                        continue;
                    ans[j] = people[i];
                    break;
                }
                else if(ans[j].size() == 0 || ans[j][0] >= currPerson[0])
                    currPerson[1]--;
            }
        }
        return ans;
    }
};