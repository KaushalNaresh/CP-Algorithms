/*

    You are given a rectangular cake of size h x w and two arrays of integers horizontalCuts and verticalCuts where:
    horizontalCuts[i] is the distance from the top of the rectangular cake to the ith horizontal cut and similarly, and
    verticalCuts[j] is the distance from the left of the rectangular cake to the jth vertical cut.
    Return the maximum area of a piece of cake after you cut at each horizontal and vertical position provided in the arrays
    horizontalCuts and verticalCuts. Since the answer can be a large number, return this modulo 109 + 7.

*/

#include<bits/stdc++.h>
using namespace std;

int main(){

    int h, w, hCuts, vCuts, cut, prevH = 0, prevV = 0, maxArea = INT_MIN;
    cin>>h>>w;
    vector<int> horizontal, vertical;
    cin>>hCuts>>vCuts;

    for(int i = 0; i < hCuts; i++){
        cin>>cut;
        horizontal.push_back(cut);
    }

    sort(horizontal.begin(), horizontal.end());

    for(int i = 0; i < vCuts; i++){
        cin>>cut;
        vertical.push_back(cut);
    }

    sort(vertical.begin(), vertical.end());

    if(vertical[vertical.size()-1] != w)
        vertical.push_back(w);
    if(horizontal[horizontal.size()-1] != h)
        horizontal.push_back(h);

    for(int i = 0; i < vertical.size(); i++){
        int width = vertical[i]-prevV;
        prevH = 0;
        for(int j = 0; j < horizontal.size(); j++){
            int height = horizontal[j]-prevH;
            int currArea = height*width;
            if(currArea > maxArea)
                maxArea = currArea;
            prevH = horizontal[j];
        }
        prevV = vertical[i];
    }

    cout<<maxArea%1000000007<<endl;
}