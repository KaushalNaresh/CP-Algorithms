#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countCompleteSubarrays(vector<int>& nums) {
        
        unordered_map<int, int> count1, count2;
        int n = nums.size();
        
        for(int i = 0; i < n; i++)
            count1[nums[i]];
        
        int lptr = 0, rptr = 0, ans = 0;
        
        while(rptr < n){

            count2[nums[rptr]] += 1;
            rptr++;

            while(count2.size() == count1.size()){
                ans += n-rptr+1;
                count2[nums[lptr]]--;
                if(count2[nums[lptr]] == 0)
                    count2.erase(nums[lptr]);
                lptr++;
            }
        }
        
        return ans;
        
    }
};