#include<bits/stdc++.h>
using namespace std;

/* Definition for singly-linked list. */

struct ListNode {
    int val;
    ListNode *next;

    ListNode(){
        val = 0;
        next = NULL;
    }

    ListNode(int x){
        val = x;
        next = NULL;
    }
    
};
 

class Solution {
public:

    void print(ListNode* head){

        ListNode* temp = head;

        while(temp != NULL){
            cout<<temp->val;
            temp = temp->next;
        }
        cout<<endl;
    }

    ListNode* reverseKGroup(ListNode* head, int k) { 
        
        ListNode* temp = head, *prev = NULL, *temp_prev = NULL, *temp_head = NULL, *new_head = NULL;

        while(temp != NULL){
            temp_prev = NULL;
            int i = 0;
            
            while(temp && i != k){
                if(i == 0)
                    temp_head = temp;
                ListNode* next = temp->next;
                temp->next = temp_prev;
                temp_prev = temp;
                temp = next;
                i++;
            }

            if(i < k)
                temp_prev = reverseKGroup(temp_prev, i);
            if(prev == NULL)
                new_head = temp_prev;
            else
                prev->next = temp_prev;
            prev = temp_head;
        }

        return new_head;
    }
};

int main(){

    int k;
    cin>>k;

    Solution* soln = new Solution();
    
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    soln->print(soln->reverseKGroup(head, k));
}