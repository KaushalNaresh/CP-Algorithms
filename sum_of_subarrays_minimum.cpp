#include<bits/stdc++.h>
using namespace std;

// class Solution {
// public:
//   int sumSubarrayMins(vector<int>& A) {
//     stack<pair<int, int>> in_stk_p, in_stk_n;
//     // left is for the distance to previous less element
//     // right is for the distance to next less element
//     vector<int> left(A.size()), right(A.size());
//     int n = A.size();
		
//     //initialize
//     for(int i = 0; i < A.size(); i++) left[i] =  i + 1;
//     for(int i = 0; i < A.size(); i++) right[i] = A.size() - i;
		
//     for(int i = 0; i < A.size(); i++){
//       // for previous less
//       while(!in_stk_p.empty() && in_stk_p.top().first > A[i]) in_stk_p.pop();
//       left[i] = in_stk_p.empty()? i + 1: i - in_stk_p.top().second;
//       in_stk_p.push({A[i],i});
			
//       // for next less
//       while(!in_stk_n.empty() && in_stk_n.top().first > A[i]){
//         auto x = in_stk_n.top();in_stk_n.pop();
//         right[x.second] = i - x.second;
//       }
//       in_stk_n.push({A[i], i});
//     }

//     for(int i = 0; i < n; i++)
//         cout<<left[i]<<" ";
//     cout<<endl;

//     for(int i = 0; i < n; i++)
//         cout<<right[i]<<" ";
//     cout<<endl;

//     long long int ans = 0, mod = 1e9 +7;
//     for(int i = 0; i < A.size(); i++){
//       ans = (ans + (A[i]%mod)*(left[i]%mod)*(right[i]%mod))%mod;
//     }
//     return ans;
//   }
// };

class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        
        int n = arr.size();
        vector<int> left(n), right(n);

        for(int i = 0; i < n; i++)
            left[i] = i+1; // Dist between curr number and its PLE

        for(int i = 0; i < n; i++)
            right[i] = n-i;  // Dist between curr number and its NLE

        vector<int> stack;

        for(int i = 0; i < n; i++){
            while(!stack.empty()){
                if(arr[stack.back()] > arr[i])
                    stack.pop_back();
                else{
                    left[i] = i-stack.back();
                    break;
                }
            }
            stack.push_back(i);
        }

        stack = {};

        for(int i = n-1; i >= 0; i--){
            while(!stack.empty()){
                if(arr[stack.back()] >= arr[i])
                    stack.pop_back();
                else{
                    right[i] = stack.back()-i;
                    break;
                }
            }
            stack.push_back(i);
        }

        long long int res = 0, mod = 1e9 + 7;

        for(int i = 0; i < n; i++)
            res = res + ((arr[i]%mod)*(left[i]%mod)*(right[i]%mod))%mod;

        return res%mod;
    }
};