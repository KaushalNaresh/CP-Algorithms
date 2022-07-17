#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    
    string minWindow(string s, string t) {
        
        int sn = s.size();
        int tn = t.size();
        
        if(tn > sn)
            return "";
        
        unordered_map<char, int> t_map, s_map;
        
        for(int i = 0; i < tn; i++)
            t_map[t[i]]+=1;
        
        int lptr = 0, rptr = 0, minLen = INT_MAX, currLen, needed = t.size(), inHand = 0;
        string minStr = "";
        
        while(rptr < sn || inHand == needed){
            
           if(inHand < needed){
               if(t_map.count(s[rptr])){
                    s_map[s[rptr]] += 1;
                    if(s_map[s[rptr]] <= t_map[s[rptr]])
                        inHand += 1;
               }
               rptr += 1;
           }
            else{
                currLen = rptr-lptr;
                if(currLen < minLen){
                    minLen = currLen;
                    minStr = s.substr(lptr, currLen);
                }
                if(t_map.count(s[lptr])){
                    s_map[s[lptr]] -= 1;
                    if(s_map[s[lptr]] < t_map[s[lptr]])
                        inHand -= 1;
                }
                lptr += 1;
            }   
        }
        return minStr;
    }
};