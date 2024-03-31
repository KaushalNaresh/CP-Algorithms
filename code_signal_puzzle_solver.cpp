/*
You are given a matrix of integers field of size height × width representing a game field, and also a matrix of integers figure of size 3 × 3 representing a figure. 
Both matrices contain only 0s and 1s, where 1 means that the cell is occupied, 
and 0 means that the cell is free.

You choose a position at the top of the game field where you put the figure and then drop it down. 
The figure falls down until it either reaches the ground (bottom of the field) or lands on an occupied cell, 
which blocks it from falling further. After the figure has stopped falling, 
some of the rows in the field may become fully occupied.

Your task is to find the dropping position such that at least one full row is formed. 
As a dropping position, you should return the column index of the cell in the game field which matches the top left corner of the figure’s 3 × 3 matrix. 
If there are multiple dropping positions satisfying the condition, feel free to return any of them. If there are no such dropping positions, return -1.

Note: The figure must be dropped so that its entire 3 × 3 matrix fits inside the field, even if part of the matrix is empty. 
*/

#include<bits/stdc++.h>
using namespace std;

int solution(vector<vector<int>> field, vector<vector<int>> figure){

    int rows = field.size();
    int cols = field[0].size();
    int figure_size = figure.size();

    for(int i = 0; i < cols-figure_size+1; i++){
        int row = 0;
        while(row < rows-figure_size+1){
            bool canFit = true;

            for(int dy = 0; dy < figure_size; dy++){
                for(int dx = 0; dx < figure_size; dx++){
                    if(field[row+dy][i+dx] == 1 && figure[dy][dx] == 1)
                        canFit = false;
                }
            }
            if(!canFit)
                break;
            row += 1;
        }
        row-=1;

        for(int dy = 0; dy < figure_size; dy++){
            bool rowFilled = true;
            for(int k = 0; k < cols; k++){
                if(!(field[row+dy][k] == 1 || 
                    ((k >= i && k < i+figure_size) && figure[dy][k-i] == 1))
                  ){
                    rowFilled = false;
                }
            }
            if(rowFilled)
                return i;
        }
    }
    return -1;
}

int main(){

    vector<vector<int>> field = {{0, 0, 0, 0},
          {0, 0, 0, 0},
          {0, 0, 0, 0},
          {1, 0, 0, 1},
          {1, 1, 0, 1}};

    vector<vector<int>> figure = {{1, 1, 0},
          {1, 0, 0},
          {1, 0, 0}};

    cout<<solution(field, figure)<<endl;
}