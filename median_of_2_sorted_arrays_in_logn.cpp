#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        
        int n1 = nums1.size(), n2 = nums2.size();
        if(n1 > n2){
            vector<int> temp = nums1;
            nums1 = nums2;
            nums2 = temp;
        }
        n1 = nums1.size(), n2 = nums2.size();
        
        if(n1 == 0){
            if(n2%2)
                return nums2[n2/2];
            else
                return (nums2[n2/2]+nums2[(n2-1)/2])/2.0;
        }
        
        int LB = 0, UB = nums1.size()-1;
        
        while(true){
            
            int partition1 = LB <= UB ? (LB+UB)/2 : -1;
            int partition2 = (n1+n2+1)/2-(partition1+1)-1;
            
            int left1 = partition1 >= 0 ? nums1[partition1] : INT_MIN;
            int left2 = partition2 >= 0 ? nums2[partition2] : INT_MIN; 
            int right1 = partition1+1 < n1 ? nums1[partition1+1] : INT_MAX;
            int right2 = partition2+1 < n2 ? nums2[partition2+1] : INT_MAX;
            
            if(left1 <= right2 && left2 <= right1){
                if((n1+n2)%2)
                    return max(left1, left2);
                else
                    return (max(left1, left2) + min(right1, right2))/2.0;
            }
            else if(left1 > right2)
                UB = partition1-1;
            else
                LB = partition1+1;
        }
    }
};