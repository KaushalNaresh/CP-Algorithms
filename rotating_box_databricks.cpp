#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    
    void swap(vector<vector<char>>& box, int row, int rptr, int lptr){
        char temp = box[row][lptr];
        box[row][lptr] = box[row][rptr];
        box[row][rptr] = temp;
    }
    
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
        
        int rows = box.size(), cols = box[0].size();
        
        for(int i = 0; i < rows; i++){
            int lptr = 0, rptr = 0;
            while(rptr < cols){
                if(box[i][rptr] == '*'){  // if obstacle
                    rptr++;
                    lptr = rptr;
                    continue;
                }
                else if(box[i][rptr] == '.'){  // if empty
                    if(box[i][lptr] != '#'){  // if stone
                        lptr++;
                    }
                    else{
                        swap(box, i, rptr, lptr);
                        lptr++;
                    }
                }
                rptr++;
            }
        }
        
        vector<vector<char>> ans(cols, vector<char>(rows));
        
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                ans[j][rows-i-1] = box[i][j];
            }
        }
        
        return ans;
    }
};