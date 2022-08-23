#include<bits/stdc++.h>
using namespace std;

bool measure(int j1, int j2, int l){

    queue<pair<int, int>> q;
    q.push({0, 0});

    set<pair<int, int>> visited;
    visited.insert({0, 0});

    while(!q.empty()){

        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        if(x+y == l)
            return true;
        
        set<pair<int, int>> temp;

        temp.insert({x, j2});
        temp.insert({j1, y});
        temp.insert({0, y});
        temp.insert({x, 0});
        temp.insert({x+min(j1-x, y), y-min(j1-x, y)});
        temp.insert({x-min(j2-y, x), y+min(j2-y, x)});

        for(auto itr = temp.begin(); itr != temp.end(); itr++){
            if(visited.find(*itr) == visited.end()){
                visited.insert(*itr);
                q.push(*itr);
            }
        }
    }

    return false;

}

int main(){

    int j1, j2, l;
    cin>>j1>>j2>>l;

    cout<<measure(j1, j2, l);
}