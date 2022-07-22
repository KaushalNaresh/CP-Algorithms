#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    static bool compare(pair<pair<int, int>, int> val, pair<pair<int, int>, int> p1){
        return p1.first.first >= val.first.second;
    }

    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        
        int n = profit.size();
        vector<pair<pair<int, int>, int>> vec(n);

        for(int i = 0; i < n; i++){
            vec[i] = {{startTime[i], endTime[i]}, profit[i]};
        }

        sort(vec.begin(), vec.end());
        vector<int> dp(n);
        dp[n-1] = vec[n-1].second;
        int maxSoFar = vec[n-1].second;
        
        for(int i = n-2; i >= 0; i--){
            auto itr = upper_bound(vec.begin()+i+1, vec.end(), vec[i], compare);
            int maxAfterEnd = itr == vec.end() ? 0 : dp[itr-vec.begin()];
            dp[i] = max(vec[i].second+maxAfterEnd, dp[i+1]);
            if(dp[i] > maxSoFar)
                maxSoFar = dp[i];
        }

        return maxSoFar;
    }
};

int main(){

    Solution *sol = new Solution();
    vector<int> startTime = {3,3,2,1};
    vector<int> endTime = {6,5,4,3};
    vector<int> profit = {70,40,10,50};
    int ans = sol->jobScheduling(startTime, endTime, profit);
    cout<<"Solution is : "<<ans;
}