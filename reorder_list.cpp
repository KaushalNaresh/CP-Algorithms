#include<bits/stdc++.h>
using namespace std;

/* Definition for singly-linked list. */
 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
    
    int getlen(ListNode* head){
        
        ListNode* temp = head;
        int len = 0;
        
        while(temp){
            temp = temp->next;
            len++;
        }
        
        return len;
    }
    
    ListNode* reverselist(ListNode* head, ListNode* prevofl1){
        
        ListNode *curr = head, *prev = nullptr, *temp;
        
        while(curr){
            temp = curr->next;
            curr->next = prev;  
            prev = curr;  
            curr = temp;  
        }
        
        return prev;
    }
    
    void insert(ListNode* l1, ListNode* l2){
        
        ListNode *node, *temp1 = l1, *temp2 = l2;
        while(temp1 != nullptr && temp2 != nullptr){
            node = temp1->next;
            temp1->next = temp2;
            temp2 = temp2->next;
            temp1->next->next = node;
            temp1 = node;
        }
        
        if(temp1 == nullptr && temp2 == nullptr)
            return;
        if(temp1 == nullptr)
            temp2 = temp1;
        else if(temp2 == nullptr)
            temp1 = temp2;
    }
    
    void print(ListNode* head){
        
        ListNode* temp = head;
        
        while(temp){
            cout<<temp->val<<" ";
            temp = temp->next;
        }
        cout<<endl;
    }
    
    void reorderList(ListNode* head) {
        
        if(head == nullptr || head->next == nullptr || head->next->next == nullptr)
            return;
        
        int len = getlen(head);
        int mid = len%2 == 0 ? (len/2) : (len/2)+1, lenofl1 = mid;
        ListNode *temp = head, *prev = nullptr;
        
        while(mid){
            prev = temp;
            temp = temp->next;
            mid--;
        }
        
        ListNode* head2 = reverselist(temp, prev);
        prev->next = nullptr;
        insert(head, head2);
    }
};