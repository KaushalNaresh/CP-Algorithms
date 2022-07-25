#include<bits/stdc++.h>
using namespace std;

/*Definition for singly-linked list.*/
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    
    pair<pair<int, int>, char> getNextCell(int r, int c, char direc, vector<vector<int>>& matrix){
        
        int rows = matrix.size();
        int cols = matrix[0].size();
        
        if(direc == 'r'){
            if(c+1 < cols && matrix[r][c+1] == 10001)
                return {{r, c+1}, 'r'};
            else
                return {{r+1, c}, 's'};
        }
        if(direc == 's'){
            if(r+1 < rows && matrix[r+1][c] == 10001)
                return {{r+1, c}, 's'};
            else
                return {{r, c-1}, 'l'};
        }
        if(direc == 'l'){
            if(c-1 >= 0 && matrix[r][c-1] == 10001)
                return {{r, c-1}, 'l'};
            else
                return {{r-1, c}, 'n'};
        }
        if(direc == 'n'){
            if(r-1 >= 0 && matrix[r-1][c] == 10001)
                return {{r-1, c}, 'n'};
            else
                return {{r, c+1}, 'r'};
        }
        return {{0, 0},'r'};
    }
    
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        
        int r = 0, c = 0;
        char direc = 'r';
        ListNode* temp = head;
        vector<vector<int>> matrix(m, vector<int>(n, 10001));
        
        while(temp){
            matrix[r][c] = temp->val;
            temp = temp->next;
            pair<pair<int, int>, char> ret = getNextCell(r, c, direc, matrix);  
            r = ret.first.first;
            c = ret.first.second;
            direc = ret.second;
        }
        
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(matrix[i][j] == 10001)
                    matrix[i][j] = -1;
            }
        }
        
        return matrix;
    }
};