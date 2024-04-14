#include<bits/stdc++.h>
using namespace std;

vector<string> ans;

void get_all_permutations(string s, int visited, string curr, char middle){

    if(curr.size() == s.size()){
        string right_half = curr;
        reverse(right_half.begin(), right_half.end());
        if(middle != '0'){
            string temp = curr+middle+right_half;
            ans.push_back(temp);
        }
        else{
            string temp = curr+right_half;
            ans.push_back(temp);
        }
        return;
    }

    for(int i = 0; i < s.size(); i++){
        if(visited & (1 << i) == 0){
            visited = visited | 1 << i;
            get_all_permutations(s, visited, curr+s[i], middle);
            visited &= ~(1 << i); 
        }
    }

    return;

}

vector<string> solution(string s){

    unordered_map<char, int> map;
    int n = s.size(), count = 0;
    string half = "";
    char middle = '0';

    for(int i= 0; i < n; i++){
        if(map.find(s[i]) == map.end()){
            map[s[i]] = 1;
        }
        else{
            map[s[i]] += 1;
        }
    }

    if(n%2 == 0){
        for(auto itr = map.begin(); itr != map.end(); itr++){
            if(itr->second % 2 != 0)
                return {};
            for(int i = 0; i < itr->second/2; i++)
                half += itr->first;
        }

    }
    else{
        for(auto itr = map.begin(); itr != map.end(); itr++){
            if(itr->second % 2 != 0){
                count += 1;
                middle = itr->first;
                for(int i = 0; i < (itr->second-1)/2; i++)
                    half += itr->first;
            }
            else
                for(int i = 0; i < itr->second/2; i++)
                    half += itr->first;
        }

        if(count > 1)
            return {};
    }

    get_all_permutations(half, 0, "", middle);

    return ans;

}

int main(){
    string s;
    cin>>s;

    vector<string> ans = solution(s);

    for(int i = 0; i < ans.size(); i++){
        cout<<ans[i]<<" ";
    }
}