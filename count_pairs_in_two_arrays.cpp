#include<bits/stdc++.h>
using namespace std;

class Solution{
    public:
    long long countPairs(vector<int>& nums1, vector<int>& nums2){
        int n = nums1.size(), ans = 0;
        vector<int> nums(n);
        for(int i = 0; i < n; i++){
            nums[i] = nums2[i]-nums1[i];
        }
        sort(nums.begin(), nums.end());
        for(int i = 0; i < n; i++){
            auto itr = upper_bound(nums.begin()+i+1, nums.end(), -nums[i]);
            ans += nums.end()-itr;
        }
        return ans;
    }
};