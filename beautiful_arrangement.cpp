#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    
    int count(int n, vector<int>& vec){
        
        if(n <= 1)
            return 1;
        
        int ans = 0;
        
        for(int i = 0; i < n; i++){
            if(vec[i]%n == 0 || n%vec[i] == 0){
                swap(vec[i], vec[n-1]);
                ans += count(n-1, vec);
                swap(vec[i], vec[n-1]);
            }
            
        }
        
        return ans;
    }
    
    int countArrangement(int n) {
        
        vector<int> vec;
        for(int i = 0; i < n; i++)
            vec.push_back(i+1);
        
        return count(n, vec);
    }
};