#include<bits/stdc++.h>
using namespace std;

vector<int> topoSort(vector<int> adj[], int v) {
    vector<int> indegree(v);
    for (int i = 0; i < v; ++i) {
        for (auto& j : adj[i]) {
            indegree[j]++;
        }
    }
    queue<int> q;
    for (int i = 0; i < v; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    vector<int> output;
    while (!q.empty()) {
        auto front = q.front();
        q.pop();
        output.push_back(front);
        for (auto& nbr : adj[front]) {
            if (--indegree[nbr] == 0) {
                q.push(nbr);
            }
        }
    }
    return output;
}
vector<char> getAlienLanguage(string* dictionary, int n) {
    // n = no of words in dictionary
    // no of vertices = no of unique characters present in the dictionary
    unordered_set<char> hashSet;
    for (int i = 0; i < n; ++i) {
        for (auto& ch : dictionary[i]) {
            hashSet.insert(ch);
        }
    }
    // calculate no of vertices
    int v = hashSet.size();
    // make the graph
    vector<int> adj[v];
    for (int i = 0; i < n - 1; ++i) {
        string curr = dictionary[i];
        string next = dictionary[i + 1];
        int length = min(curr.length(), next.length());
        for (int j = 0; j < length; ++j) {
            // as soon as we get first mis-match
            if (curr[j] != next[j]) {
                adj[curr[j] - 'a'].push_back(next[j] - 'a');
                break;
            }
        }
    }

    // do topo sort to get the sorted ordering
    vector<int> output = topoSort(adj, v);
    vector<char> ans;
    for (auto& val : output) {
        ans.push_back(val + 'a');
    }
    return ans;
}

int main(){

    vector<string> words = {"rgdcsqcbkmksormnultmifcqzyhfiecemfrarrjavzsfjjulamrrgvnjvmfjmfutvrbmapbcjjbdlpgmwhtmluxhhrchdokgqteo", "tmonqbvoeevajolnktcvnyaskynoulktbofblxbheiqyiclcbpebbwmuzsdosknmbeoryeejtybvtpgghsniicyizgcfaqajsrij", "gkrsgyjmhcfutefpxmuzqdptzwoyirzyxpyqygboweyuslarsksjyiiakcnjjvlqbynzngkfdgrbrpypwdndpytygcszkmouchom", "irxxmyfbwrxenzrwfxoicfphlzlroaxitagtiodscuchdhjylxfkrjmwmzdtmymeyerihjrdppmitipnzezfrqvhvlqykykgpcce", "bmbhhozjevhvspwepgepmzkqreqqynjndgtugkuaauvmajbeubaqnlguhbgwttyirwkmzgtpouvwnxepmetqyczdiqfwtucmpsqt"};
    vector<char> ans = getAlienLanguage(&words[0], 5);

    for(auto c : ans)
        cout<<c;
    cout<<endl;
}