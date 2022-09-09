/*
    Question : https://cybergeeksquad.co/2022/02/decode-string-frequency-amazon-oa.html
*/

#include<bits/stdc++.h>
using namespace std;

int main(){

    string encode, ans = "";
    cin>>encode;

    int lptr = 0;
    while(lptr < encode.size()){

        if(encode[lptr] >= '0' && encode[lptr] <= '9'){
            if(lptr+2 < encode.size() && encode[lptr+2] == '#'){
                ans += 'a'+(stoi(encode.substr(lptr, 2))-1);
                lptr+=3;
            }
            else{
                ans += 'a'+ (encode[lptr]-'0'-1);
                lptr++;
            }
        }
        else if(encode[lptr] == '('){
            char end = ans[ans.size()-1];
            string numb = "";
            lptr++;
            while(encode[lptr] >= '0' && encode[lptr] <= '9'){
                numb += encode[lptr];
                lptr++;
            }
            string temp(stoi(numb)-1, end);
            ans+=temp;
            lptr++;
        }
    }

    cout<<ans;
}