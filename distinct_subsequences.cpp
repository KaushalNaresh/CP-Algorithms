#include<bits/stdc++.h>
using namespace std;

int main(){

    string s, t;
    cin>>s>>t;

    int s_n = s.size(), t_n = t.size();

    vector<vector<int>> vec(s_n+1, vector<int>(t_n+1, 0));

    for(int i = 0; i <= t_n; i++)
        vec[0][i] = 1;

    for(int i = 1; i <= s_n; i++){
        for(int j = 1; j <= t_n; j++){
            if(s[i-1] == t[j-1])
                vec[i][j] = vec[i-1][j-1]+vec[i][j-1];
            else
                vec[i][j] = vec[i][j-1];
        }
    }

    cout<<vec[s_n][t_n];

}