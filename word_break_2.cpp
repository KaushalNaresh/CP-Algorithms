#include<bits/stdc++.h>
using namespace std;

class trieNode{
    public:
    
    vector<trieNode*> next;
    bool isWord;
    
    trieNode(){
        isWord = false;
        next = vector<trieNode*>(26, nullptr);
    }
};
class Trie{
    public:
    
    trieNode* root;
    
    Trie(){
        root = new trieNode();
    }
    
    void addWord(string word){
        
        trieNode* node = root;
        
        for(auto c : word){
            if(!node->next[c-'a'])
                node->next[c-'a'] = new trieNode();
            node = node->next[c-'a'];
        }
        node->isWord = true;
    }
    
    bool find(string word){
        
        trieNode* node = root;
        
        for(auto c : word){
            if(!node->next[c-'a'])
                return false;
            node = node->next[c-'a'];
        }
        
        return node->isWord;
    }
};

class Solution {
public:
    
    void wordBreakUtil(string &s, Trie* trie, int idx, vector<string> &ans, string curr){
        
        if(idx >= s.size()){
            ans.push_back(curr);
            return;
        }
        
        if(curr != "")
            curr+=" ";
        
        trieNode* node = trie->root;
        
        for(int i = idx; i < s.size(); i++){
            
            if(node->next[s[i]-'a']){
                node = node->next[s[i]-'a'];
                curr += s[i];
            }
            else
                return;
            
            if(node->isWord)
                wordBreakUtil(s, trie, i+1, ans, curr);
        }
        
        return;
            
    }
    
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        
        Trie* trie = new Trie();
        vector<string> ans;
        int idx = 0;
        string curr = "";
        
        for(auto word : wordDict){
            trie->addWord(word);
        }
        
        wordBreakUtil(s, trie, idx, ans, curr);
        return ans;
    }
};