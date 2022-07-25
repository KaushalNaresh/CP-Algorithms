#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int calculate(string s) {
        
        vector<string> stack;
        string postFix = "", curr, newStr = "( ", prev = "";
        int n = s.size();

        for(int i = 0; i < n; i++){
            if(s[i] >= '0' && s[i] <= '9')
                newStr+=s[i];
            else{
                newStr+=" ";
                newStr+=s[i];
                newStr+=" ";
            }
        }
        newStr += " )";
        stringstream ss(newStr);
        
        while(ss >> curr){
            if(curr == "+" || curr == "-"){
                if(curr == "-" && prev == "(" ){
                    stack.push_back("-");
                    stack.push_back("#");
                }
                else{
                    while(!stack.empty() && (stack.back() == "+" || stack.back() == "-" || stack.back() == "#")){
                        postFix+=stack.back();
                        postFix+=" ";
                        stack.pop_back();
                    }
                    
                    stack.push_back(curr);
                }
            }
            else if(curr == "(")
                stack.push_back(curr);
            else if(curr == ")"){
                while(!stack.empty() && stack.back() != "("){
                    postFix+=stack.back();
                    postFix+=" ";
                    stack.pop_back();
                }
                stack.pop_back();
            }
            else{
                postFix+=curr;
                postFix+=" ";
            }
            prev = curr;
        }
       
        while(!stack.empty()){
            postFix+=stack.back();
            postFix+=" ";
            stack.pop_back();
        }

        cout<<postFix<<endl;

        vector<int> stack2;
        stringstream ss2(postFix);
        bool unary = false;

        while(ss2>>curr){
            if(curr != "+" && curr != "-" && curr != "#")
                stack2.push_back(stoi(curr));
            else if(curr == "#"){
                unary = true;
                continue;
            }
            else{
                int n1 = stack2.back();
                stack2.pop_back();
                if(curr == "-" && unary){
                    stack2.push_back(-n1);
                    unary = false;
                }
                else if(curr == "-"){
                    int n2 = stack2.back();
                    stack2.pop_back();
                    stack2.push_back(n2-n1);
                }
                else if(curr == "+"){
                    int n2 = stack2.back();
                    stack2.pop_back();
                    if(curr == "+")
                        stack2.push_back(n1+n2);
                }
            }
        }

        return !stack2.empty() ? stack2.back() : 0;
    }
};

int main(){

    Solution* sol = new Solution();
    string s = "(1+(4+5+2)-3)+(6+8)";
    cout<<sol->calculate(s);
}