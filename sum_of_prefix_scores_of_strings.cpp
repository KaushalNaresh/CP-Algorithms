#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    
    class TrieNode{
        
        public:
        vector<TrieNode*> neigh;
        int count;
        
        TrieNode(){
            count = 0;
            neigh = vector<TrieNode*>(26, nullptr);
        }
        
        void addWord(string word){
            
            TrieNode* node = this;
            
            for(int i = 0; i < word.size(); i++){
                if(node->neigh[word[i]-'a'] == nullptr)
                    node->neigh[word[i]-'a'] = new TrieNode();
                node->neigh[word[i]-'a']->count += 1;
                node = node->neigh[word[i]-'a'];
            }
        }
        
        int score(string word){
            
            TrieNode* node = this;
            int score = 0;
            
            for(int i = 0; i < word.size(); i++){
                if(node->neigh[word[i]-'a'] != nullptr)
                    score+=node->neigh[word[i]-'a']->count;
                node = node->neigh[word[i]-'a'];
            }
            
            return score;
        }
    };
    
    vector<int> sumPrefixScores(vector<string>& words) {
        
        TrieNode* root = new TrieNode();
        
        for(int i = 0; i < words.size(); i++){
            root->addWord(words[i]);
        }
        
        vector<int> answer(words.size(), 0);
        
        for(int i = 0; i < words.size(); i++){
            answer[i] = root->score(words[i]);
        }
        
        return answer;
    }
};