#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    /*
        Time Complexity : O(n*nlogn) extra n is coming because of linked list operations
        Space Complexity : O(n)
    */
    vector<int> countSmaller(vector<int>& nums) {
        
        int n = nums.size();
        list<int> l(nums.begin(), nums.end());
        vector<int> ans(n);
        ans[n-1] = 0;
        
        for(int i = n-2; i >= 0; i--){
            auto beg = l.begin();
            auto itr = l.begin();
            advance(beg, i+1);
            advance(itr, i);
            int target = *itr;
            auto ret = lower_bound(beg, l.end(), target);
            int dist = distance(beg, ret);
            l.erase(itr);
            l.insert(ret, target);
            ans[i] = dist;
        }
        
        return ans;
    }

    /*
        Time Complexity : O(nlogn) using merge sort
        space complexity : O(nlogn) stack + temp vector
    */
   void mergeSort(vector<pair<int, int>>& vec, vector<int>& ans, int LB, int UB){

        if(LB == UB)
            return;
        
        int mid = (LB+UB)/2, ptr1 = LB, ptr2 = mid+1;

        mergeSort(vec, ans, LB, mid);
        mergeSort(vec, ans, mid+1, UB);

        vector<pair<int, int>> temp;
        int count = 0;

        while(ptr1 <= mid && ptr2 <= UB){
            if(vec[ptr1].second <= vec[ptr2].second){
                temp.push_back(vec[ptr1]);
                ans[vec[ptr1].first] += count;
                ptr1++;
            }
            else{
                count++;
                temp.push_back(vec[ptr2]);
                ptr2++;
            }
        }

        while(ptr1 <= mid){
            temp.push_back(vec[ptr1]);
            ans[vec[ptr1].first] += count;
            ptr1++;
        }
        while(ptr2 <= UB){
            temp.push_back(vec[ptr2]);
            ptr2++;
        }

        for(int i = LB; i <= UB; i++)
            vec[i] = temp[i-LB];   
   }

   vector<int> countSmaller(vector<int>& nums) {

        int n = nums.size();
        vector<int> ans(n, 0);
        vector<pair<int, int>> vec(n);

        for(int i = 0; i < n; i++)
            vec[i] = {i, nums[i]};
        
        mergeSort(vec, ans, 0, n-1);

        return ans;
   }
};

int main(){

    Solution* sol = new Solution();
    vector<int> nums = {1};
    vector<int> ans = sol->countSmaller(nums);

    for(auto i : ans)
        cout<<i<<" ";
}