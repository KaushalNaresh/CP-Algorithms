#include<bits/stdc++.h>
using namespace std;

static bool compare(pair<int, int> p1, pair<int, int> p2){

    return p1.second <= p2.second;
}

int main(){

    int n, num;
    cin>>n;
    vector<int> vec;

    for(int i = 0; i < n; i++){
        cin>>num;
        vec.push_back(num);
    }

    vector<pair<int, int>> pVec;

    for(int i = 0; i < n; i++)
        pVec.push_back({i, vec[i]});

    sort(pVec.begin(), pVec.end(), compare);

    vector<int> visited(n, 0);
    int ans = 0;

    for(int i = 0; i < n; i++){

        if(visited[i] == 1 || pVec[i].first == i)
            continue;

        int cycleSize = 0, j = i;

        while(visited[j] != 1){
            visited[j] = 1;

            j = pVec[j].first;
            cycleSize++;
        }
        ans+=cycleSize-1;
    }

    cout<<ans<<endl;
}