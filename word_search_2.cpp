#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    
    class TrieNode{
        
        public:
        vector<TrieNode*> next;
        bool isWord;
        
        TrieNode(){
            next = vector<TrieNode*>(26, nullptr);
            isWord = false;
        }
        
        void addWord(string word){
            
            TrieNode* node = this;
            for(int i = 0; i < word.size(); i++){
                if(!node->next[word[i]-'a'])
                    node->next[word[i]-'a'] = new TrieNode();
                node = node->next[word[i]-'a'];
            }
            node->isWord = true;
        }
        
        bool search(string word){
            
            TrieNode* node = this;
            for(int i = 0; i < word.size(); i++){
                if(node->next[word[i]-'a'])
                    return false;
                node = node->next[word[i]-'a'];
            }
            
            return node->isWord;
        }
    };
    
    void findWord(int r, int c, vector<vector<char>>& board, vector<string>& ans, TrieNode* node, string s){
        
        if(r<0||r>=board.size()||c<0||c>=board[0].size()||board[r][c] == ' ')
            return;
        
        if(node->next[board[r][c]-'a']){
            
            node = node->next[board[r][c]-'a'];
            char ch = board[r][c];
            s += ch;
            board[r][c] = ' ';
        
            if(node->isWord){
                ans.push_back(s);
                node->isWord = false;
            }
        
            findWord(r+1, c, board, ans, node, s);
            findWord(r-1, c, board, ans, node, s);
            findWord(r, c+1, board, ans, node, s);
            findWord(r, c-1, board, ans, node, s);

            board[r][c] = ch;
        }
        
        return;
    }
    
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        
        int rows = board.size();
        int cols = board[0].size();
        
        vector<vector<int>> visited(rows, vector<int>(cols, 0));
        
        TrieNode* root = new TrieNode();
        
        for(int i = 0; i < words.size(); i++)
            root->addWord(words[i]);
            
        vector<string> ans;
        
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                findWord(i, j, board, ans, root, "");
            }
        }
        
        return ans;
    }
};