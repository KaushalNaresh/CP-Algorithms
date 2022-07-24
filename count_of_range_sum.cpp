#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    void merge(vector<long>& sums, int LB1, int UB1, int LB2, int UB2){

        int ptr1 = LB1, ptr2 = UB2;
        vector<long> temp; 
        while(LB1 <= UB1 && LB2 <= UB2){
            if(sums[LB1] <= sums[LB2]){
                temp.push_back(sums[LB1]);
                LB1++;
            }
            else{
                temp.push_back(sums[LB2]);
                LB2++;
            }
        }

        while(LB1 <= UB1){
            temp.push_back(sums[LB1]);
            LB1++;
        }

        while(LB2 <= UB2){
            temp.push_back(sums[LB2]);
            LB2++;
        }

        for(int i = ptr1; i <= ptr2; i++){
            sums[i] = temp[i-ptr1];
        }
    }

    int mergeSort(vector<long>& sums, int LB, int UB, int lower, int upper){

        if(LB == UB)
            return sums[LB] >= lower && sums[LB] <= upper ? 1 : 0;
        
        int mid = (LB+UB)/2, itr1 = mid+1, itr2 = mid+1;
        int count = mergeSort(sums, LB, mid, lower, upper) + mergeSort(sums, mid+1, UB, lower, upper);
        
        for(int i = LB; i <= mid; i++){
            while(itr1 <= UB && sums[itr1]-sums[i] < lower) itr1++;
            while(itr2 <= UB && sums[itr2]-sums[i] <= upper) itr2++;
            count += itr2-itr1;
        }
        merge(sums, LB, mid, mid+1, UB);
        
        return count;
    }

    int countRangeSum(vector<int>& nums, int lower, int upper) {
        
        int n = nums.size();
        vector<long> sums(n+1, 0);

        for(int i = 1; i <= n; i++)
            sums[i] = sums[i-1]+nums[i-1];

        return mergeSort(sums, 1, n, lower, upper);
    }
};

int main(){

    Solution* sol = new Solution();
    vector<int> nums = {-2147483647,0,-2147483647,2147483647};
    int lower = -564, upper = 3864;
    cout<<sol->countRangeSum(nums, lower, upper);
}