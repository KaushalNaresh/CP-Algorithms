#include<bits/stdc++.h>
using namespace std;

int main(){

    int n, xor_val = 0, set1 = 0, set2 = 0, num;
    cin>>n;
    vector<int> vec(n);

    for(int i = 1; i <= n; i++){
        cin>>num;
        vec[i-1] = num;
        xor_val ^= (i^vec[i-1]);
    }

    int set_bit = 0;
    while((int)(xor_val&1) != 1){
        xor_val>>1;
        set_bit++;
    }
    
    for(int i = 1; i <= n; i++){
        if((int)(i>>set_bit&1) == 1)
            set1 ^= i;
        else
            set2 ^= i;
        
        if((int)(vec[i-1]>>set_bit&1) == 1)
            set1 ^= vec[i-1];
        else
            set2 ^= vec[i-1];
    }

    for(int i = 0; i < n; i++){
        if(vec[i] == set1){
            cout<<set2<<endl;
            break;
        }
        else if(vec[i] == set2){
            cout<<set1<<endl;
            break;
        }
    }
}