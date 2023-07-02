#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    
    long long continuousSubarrays(vector<int>& nums) {
        
        deque<int> maxdq, mindq;
        
        int n = nums.size(), i = 0, j = 0;
        long long count = 0;
        
        while(i < n){
            
            while(!maxdq.empty() && maxdq.back() < nums[i])
                maxdq.pop_back();
            while(!mindq.empty() && mindq.back() > nums[i])
                mindq.pop_back();
            
            maxdq.push_back(nums[i]);
            mindq.push_back(nums[i]);
            
            while(abs(maxdq.front() - mindq.front()) > 2){
                if(maxdq.front() == nums[j])
                    maxdq.pop_front();
                if(mindq.front() == nums[j])
                    mindq.pop_front();
                j++;
            } 
            count += (i-j)+1;
            i++;
        }
        
        return count;
    }
};