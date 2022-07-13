#include<bits/stdc++.h>
using namespace std;

class Solution{

    public:

    bool dfs(unordered_map<char, set<char>>& graph, unordered_map<char, bool>& visited, char c, string& res){

        if(visited.find(c) != visited.end())  // if c exists in visited the return its value in visited dict
            return visited[c];

        visited[c] = true;

        for(auto itr : graph[c]){
            if(dfs(graph, visited, itr, res))
                return true;
            
        }
       
        visited[c] = false;
        res += c;
        return false;
    }

    // Topological sort using dfs 
    // Time Complexity : O(V+E)
    string topologicalSort(unordered_map<char, set<char>>& graph){

        unordered_map<char, bool> visited;  // False -> visited and is part of final result (res), True -> part of current traversal
        string res;

        for(auto itr : graph){
            
            if(dfs(graph, visited, itr.first, res))
                return "";
        }

        reverse(res.begin(), res.end());
        return res;
    }

    string alienOrder(vector<string>& words){

        int n = words.size();
        unordered_map<char, set<char>> graph;

        // Creating graph

        for(int i = 0; i < n; i++){
            for(auto c : words[i]){
                graph[c];
            }
        }

        for(int i = 0; i < n-1; i++){
            string word1 = words[i];
            string word2 = words[i+1];

            string smallWord = word1.size() < word2.size() ? word1 : word2;
            string bigWord = word1.size() >= word2.size() ? word1 : word2;

            if(bigWord.substr(smallWord.size()) == smallWord && bigWord == word1) // if 2 words are same or
                return "";                                                        // if prefix of big word is same as small word and big word comes before small word. 
                
            for(int j = 0; j < smallWord.size(); j++){  // iterate through all adjacent words and look for first unmatched character lets say at 'j' index
                if(word1[j] != word2[j]){             // add an edge from word1[j] to word2[j]
                    graph[word1[j]].insert(word2[j]);
                    break;
                }
            }
            
        }

        return topologicalSort(graph);  // if topological order exists then return one otherwise return empty string.
    }
};

int main(){

    vector<string> words = {"rgdcsqcbkmksormnultmifcqzyhfiecemfrarrjavzsfjjulamrrgvnjvmfjmfutvrbmapbcjjbdlpgmwhtmluxhhrchdokgqteo", "tmonqbvoeevajolnktcvnyaskynoulktbofblxbheiqyiclcbpebbwmuzsdosknmbeoryeejtybvtpgghsniicyizgcfaqajsrij", "gkrsgyjmhcfutefpxmuzqdptzwoyirzyxpyqygboweyuslarsksjyiiakcnjjvlqbynzngkfdgrbrpypwdndpytygcszkmouchom", "irxxmyfbwrxenzrwfxoicfphlzlroaxitagtiodscuchdhjylxfkrjmwmzdtmymeyerihjrdppmitipnzezfrqvhvlqykykgpcce", "bmbhhozjevhvspwepgepmzkqreqqynjndgtugkuaauvmajbeubaqnlguhbgwttyirwkmzgtpouvwnxepmetqyczdiqfwtucmpsqt"};
    Solution* sol = new Solution();
    
    cout<<sol->alienOrder(words);
}