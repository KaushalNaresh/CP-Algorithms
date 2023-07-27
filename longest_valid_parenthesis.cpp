#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        
        stack<int> st;
        st.push(-1);
        int n = s.size(), maxSoFar = INT_MIN;

        for(int i = 0; i < n; i++){
            if(st.empty() || s[i] == '(')
                st.push(i);
            else{
                if(st.top() != -1 && s[st.top()] == '('){
                    st.pop();
                    int len = i-st.top();
                    if(len > maxSoFar)
                        maxSoFar = len;
                }
                else
                    st.push(i);
            }
        }

        return maxSoFar != INT_MIN ? maxSoFar : 0;
    }
};