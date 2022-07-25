#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int mergeSort(vector<int>& nums, int LB, int UB){
        if(LB == UB)
            return 0;
        int mid = (LB+UB)/2;
        int count = mergeSort(nums, LB, mid) + mergeSort(nums, mid+1, UB);
        int ptr1 = LB, ptr2 = mid+1;
        while(ptr1 <= mid && ptr2 <= UB){
            if((long)(nums[ptr1]) <= (long)(2)*nums[ptr2])
                ptr1++;
            else{
                count = count+(mid-ptr1+1);
                ptr2++;
            }
        }
        merge(nums, LB, mid, mid+1, UB);
        return count;
    }
    
    void merge(vector<int>& nums, int lb1, int ub1, int lb2, int ub2){
        
        vector<int> temp;
        int ptr1 = lb1, ptr2 = ub2;
        while(lb1 <= ub1 && lb2 <= ub2){
            if(nums[lb1] <= nums[lb2]){
                temp.push_back(nums[lb1]);
                lb1++;
            }
            else{
                temp.push_back(nums[lb2]);
                lb2++;
            }
        }
        
        while(lb1 <= ub1){
            temp.push_back(nums[lb1]);
            lb1++;
        }
        
        while(lb2 <= ub2){
            temp.push_back(nums[lb2]);
            lb2++;
        }
        
        for(int i = ptr1; i <= ptr2; i++){
            nums[i] = temp[i-ptr1];
        }
    }
    
    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        return mergeSort(nums, 0, n-1);
    }
};