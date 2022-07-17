#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    
    int getMax(vector<int>& max){
        
        int currMax = 0;
        
        for(auto i : max)
            if(currMax < i)
                currMax = i;
        
        return currMax;
    }
    
    int characterReplacement(string s, int k) {
        
        int n = s.size();
        vector<int> max(26, 0);
        int lptr = 0, rptr = 0, maxLen = INT_MIN;
        
        
        // Time Complexity O(n*26)
        while(rptr < n){
            char curr = s[rptr];
            max[curr-'A'] += 1;
            int currMax = getMax(max);
            int condn = (rptr-lptr+1)-currMax;
            
            if(condn > k){
                while(condn > k ){
                    max[s[lptr]-'A'] -= 1;
                    lptr += 1;
                    condn = (rptr-lptr+1)-getMax(max);
                }
            }
            int currLen = rptr-lptr+1;
            if(maxLen < currLen)
                maxLen = currLen;
            rptr += 1;
        }
        
        return maxLen;
    }
};