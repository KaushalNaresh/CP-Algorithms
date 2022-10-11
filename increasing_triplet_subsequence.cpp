#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        
        int n = nums.size();
        vector<int> minLeft(n, -1), maxRight(n, -1);
        int minSoFar = 0, maxSoFar = n-1;
        
        for(int i = 1; i < n; i++){
            if(nums[i] > nums[minSoFar])
                minLeft[i] = minSoFar;
            if(nums[minSoFar] > nums[i])
                minSoFar = i;
        }
        
        for(int j = n-2; j >= 0; j--){
            if(nums[j] < nums[maxSoFar])
                maxRight[j] = maxSoFar;
            if(nums[maxSoFar] < nums[j])
                maxSoFar = j;
        }
        
        for(int i = 0; i < n; i++){
            if(minLeft[i] != -1 && maxRight[i] != -1)
                return true;
        }
        
        return false;
        
    }
};