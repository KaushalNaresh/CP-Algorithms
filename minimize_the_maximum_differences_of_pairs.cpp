#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    int countValidPairs(vector<int>& nums, int threshold) {

        int count = 0, i = 0;

        while(i < nums.size()-1){

            if(abs(nums[i]-nums[i+1]) <= threshold){
                count++;
                i+=2;
            }
            else
                i++;
        }

        return count;
    } 

    int minimizeMax(vector<int>& nums, int p) {

        sort(nums.begin(), nums.end());
        int n = nums.size();

        int LB = 0, UB = nums[n-1]-nums[0];

        while(LB < UB){

            int mid = LB + (UB-LB)/2;
            int getPairs = countValidPairs(nums, mid);

            if (getPairs >= p) {
                UB = mid;
            } else {
                LB = mid + 1;
            }
        }

        return LB;
    }

};
