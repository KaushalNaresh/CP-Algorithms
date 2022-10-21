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
    
    void print(ListNode* l){
        
        while(l){
            cout<<l->val<<"->";
            l = l->next;
        }
        cout<<endl;
    }
    

    // Important 
    pair<ListNode*, int> sum(ListNode* l1, ListNode* l2){
        
        if(l1 == nullptr && l2 == nullptr)
            return {nullptr, 0};
        
        pair<ListNode*, int> p = sum(l1->next, l2->next);
        int s = l1->val + l2->val + p.second;
        int rem = s/10;
        int q = s%10;
        ListNode* node = new ListNode(q);
        node->next = p.first;
        return {node, rem};
    }
    
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        
        ListNode* temp1 = l1, *temp2 = l2, *temp = nullptr;
        int sCount = 0, count = 0;
        
        while(temp1 != nullptr && temp2 != nullptr){
            temp1 = temp1->next;
            temp2 = temp2->next;
            sCount++;
        }
        
        if(temp2 == nullptr){
            temp = l2;
            l2 = l1;
            l1 = temp;
        }
        
        while(temp1 != nullptr){
            count++;
            temp1 = temp1->next;
        }
        while(temp2 != nullptr){
            count++;
            temp2 = temp2->next;
        }
        
        ListNode* newHead = nullptr, *prev = nullptr;
        temp = nullptr;
        while(count){
            count--;
            if(newHead == nullptr){
                newHead = new ListNode(0);
                temp = newHead;
                continue;
            }
            else{
                temp->next = new ListNode(0);
            }
            temp = temp->next;
        }
        
        if(temp)
            temp->next = l1;
        else
            newHead = l1;
        
        pair<ListNode*, int> p = sum(newHead, l2);
        if(p.second == 0)
            return p.first;
        else{
            ListNode* node = new ListNode(p.second);
            node->next = p.first;
            return node;
        }
    }
};