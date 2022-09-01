#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    
    int upperBound(vector<int> nums, int start, int end, int target){

        int ans;

        while(start <= end){
            int mid = (start+end)/2;
            if(nums[mid] <= target)
                start = mid+1;
            else{
                ans = mid;
                end = mid-1;
            }
        }

        return ans;
    }
    
    void nextPermutation(vector<int>& nums) {
        
        int n = nums.size();
        bool isNext = false;
        
//         for(int i = n-1; i > 0; i--){
//             if(nums[i] > nums[i-1]){
//                 sort(nums.begin()+i, nums.end());
//                 auto itr = upper_bound(nums.begin()+i, nums.end(), nums[i-1]);
//                 iter_swap(itr, nums.begin()+(i-1));
//                 isNext = true;
//                 break;
//             }
//         }
        
//         if(!isNext)
//             sort(nums.begin(), nums.end());
        
        for(int i = n-1; i > 0; i--){
            if(nums[i] > nums[i-1]){
                sort(nums.begin()+i, nums.end());
                int idx = upperBound(nums, i, n-1, nums[i-1]);
                swap(nums[idx], nums[i-1]);
                isNext = true;
                break;
            }
        }
        
        if(!isNext)
            sort(nums.begin(), nums.end());
    }
};