#include<bits/stdc++.h>
using namespace std;

set<string> ans;

int countMoves(int start, int end, int n, int curr_idx, string &moves, vector<vector<int>> &memo, string moveSoFar){
    
    if(curr_idx == moves.size()){
        if(start == end){
            ans.insert(moveSoFar);
        }
        return start == end ? 1 : 0;
    }

    if(memo[start][curr_idx] != -1)
        return memo[start][curr_idx];

    int leftCount = 0, rightCount = 0, skipCount = 0;
    string temp = moveSoFar;

    if(moves[curr_idx] == 'l'){

        moveSoFar += 'l';
        leftCount = start > 0 ? countMoves(start-1, end, n, curr_idx+1, moves, memo, moveSoFar) : 0;
        moveSoFar = temp;
    }

    if(moves[curr_idx] == 'r'){
        moveSoFar += 'r';
        rightCount = start < n ? countMoves(start+1, end, n, curr_idx+1, moves, memo, moveSoFar) : 0;
        moveSoFar = temp;
    }

    skipCount = countMoves(start, end, n, curr_idx+1, moves, memo, moveSoFar);

    int total_moves = leftCount + rightCount + skipCount;

    memo[start][curr_idx] =  total_moves > 0 ? total_moves : -1;

    return memo[start][curr_idx];

}

int getDistinctMoveCount(string moves, int x, int y, int n){

    vector<vector<int>> memo(n+1, vector<int>(moves.size(), -1));

    countMoves(x, y, n, 0, moves, memo, "");
    for(int i = 0; i < n+1; i++){
        for(int j = 0; j < moves.size(); j++){
            cout<<memo[i][j]<<" ";
        }
        cout<<endl;
    }

    // for(auto t : ans)
    //     cout<<t<<endl;

    return ans.size();

}

int main(){

    string moves;
    int x, y, n;

    cin>>moves;
    cin>>x>>y>>n;

    cout<<getDistinctMoveCount(moves, x, y, n);
}