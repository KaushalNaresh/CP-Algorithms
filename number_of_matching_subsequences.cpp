#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    int find(vector<int> vec, int LB, int UB, int prev){

        while(LB <= UB){
            int mid = (LB+UB)/2;
            if(vec[mid] > prev)
                UB = mid-1;
            else if(vec[mid] <= prev)
                LB = mid+1;
        }
        return LB;
    }

    // Time Complexity : O(N*M*log(S)) where N is the len of list of words,
    //                                       M is the maximum word length in list of words
    //                                       S is the length of string s
    int numMatchingSubseq(string s, vector<string>& words) {

        unordered_map<char, vector< int>> occ; // stores multiple occurances of character in s

        for(int i = 0; i < s.size(); i++){
            occ[s[i]].push_back(i);
        }

        int count = 0;
        for(int i = 0; i < words.size(); i++){
            int prev = -1;
            bool found = true;
            for(auto ch : words[i]){
                if(occ.count(ch)){
                    int idx = find(occ[ch], 0, occ[ch].size()-1, prev);
                    if(idx < 0 || idx >= occ[ch].size()){
                        found = false;
                        break;
                    }
                    prev = occ[ch][idx];
                }
                else{
                    found = false;
                    break;
                }
            }
            if(found)
                count++;
        }
        return count;
    }

    // Same algorithm but using various inbuilt functions
    int numMatchingSubseq (string S, vector<string>& words) {
		vector<vector<int>> alpha (26);
		for (int i = 0; i < S.size (); ++i) alpha[S[i] - 'a'].push_back (i);
		int res = 0;

		for (const auto& word : words) {
			int x = -1;
			bool found = true;

			for (char c : word) {
				auto it = upper_bound (alpha[c - 'a'].begin (), alpha[c - 'a'].end (), x);
				if (it == alpha[c - 'a'].end ()) found = false;
				else x = *it;
			}

			if (found) res++;
		}

		return res;
	}
};

int main(){

    Solution* sol = new Solution();
    string s = "gggggggggq";
    vector<string> words = {"gq","gq","gq","gq"};
    cout<<sol->numMatchingSubseq(s, words);
}