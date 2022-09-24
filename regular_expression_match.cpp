#include<bits/stdc++.h>
using namespace std;
 
class TrieNode{
    
    public:
    vector<TrieNode*> neigh;
    bool isPrefix;
    
    TrieNode(){
        neigh = vector<TrieNode*>(26, nullptr);
        isPrefix = false;
    }    
    
    void addWord(string word){
        
        this->isPrefix = true;
        for(int i = 0; i < word.size(); i++){
            TrieNode* node = this;
            for(int j = i; j < word.size(); j++){
                if(node->neigh[word[j]-'a'] == nullptr)
                    node->neigh[word[j]-'a'] = new TrieNode();
                node = node->neigh[word[j]-'a']; 
            }
            node->isPrefix = true;
        }
    }
    
    int checkIfMatch(string pattern, TrieNode* node){
        
        // TrieNode* node = this;
        for(int i = 0; i < pattern.size(); i++){
            if(pattern[i] == '*')
                node = this;
            else if(pattern[i] == '?'){
                for(int j = 0; j < 26; j++){
                    if(node->neigh[j])
                        if(checkIfMatch(pattern.substr(i+1, pattern.size()-i-1), node->neigh[j]))
                            return 1;
                }
                return 0;
                
            }
            else{
                if(node->neigh[pattern[i]-'a'])
                    node = node->neigh[pattern[i]-'a'];
                else
                    return 0;
            }
        }
        
        return node->isPrefix == true ? 1 : 0;   
    }
};


int isMatch(const string A, const string B) {
    
    TrieNode* root = new TrieNode();
    root->addWord(A);
    return root->checkIfMatch(B, root);
}