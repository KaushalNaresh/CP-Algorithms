#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    /*
        Time Complexiy : O(klogk) where k ~ n*n
        Space Complexity : O(k)
    */

    int smallestDistancePair(vector<int>& nums, int k) {
        
        sort(nums.begin(), nums.end());
        priority_queue< pair<int, pair<int, int>>, vector< pair<int, pair<int, int>> >, greater< pair<int, pair<int, int>> > > pq;
        int n = nums.size();
        
        for(int i = 0; i < n-1; i++){
            pq.push({abs(nums[i]-nums[i+1]), {i, i+1}});
        }
        
        while(k && !pq.empty()){
            k--;
            pair<int, pair<int, int>> p = pq.top();
            int idx1 = p.second.first;
            int idx2 = p.second.second;
            pq.pop();
            if( idx2+1 < n)
                pq.push({abs(nums[idx1]-nums[idx2+1]), {idx1, idx2+1}});
            if(k == 0)
                return p.first;
        }
        return -1;
    }

    /*
        Time Complexity : O(nlogn) where n is maximum diff between nums[0] and nums[-1]
        Space Complexit : O(1)
    */

    int smallestDistancePair(vector<int>& nums, int k) {
        sort(begin(nums), end(nums));
        int l = 0, h = 1000000;
        while (l < h) {
            int m = (l + h) / 2;
            if (k <= pairsUnder(nums, m))
                h = m;
            else
                l = m + 1;
        }
        return l;
    } 
    
    int pairsUnder(vector<int>& nums, int m) {
        int j = 0, res = 0;
        for (auto i = 0; i < nums.size(); ++i) {
            while (j < nums.size() && nums[j] - nums[i] <= m)
                ++j;
            res += j - i - 1;
        }
        return res;
    }

}; 