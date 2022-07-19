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

    struct compare{
        bool operator()(ListNode* l1, ListNode*l2){
            return l1->val > l2->val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        
        priority_queue<ListNode*, vector<ListNode*>, compare> pq;
        int n = lists.size();

        for(int i = 0; i < n; i++){
            if(lists[i] != nullptr)
                pq.push(lists[i]);
        }
        
        if(pq.empty())
            return nullptr;

        ListNode* head = pq.top();
        if(head->next != nullptr)
            pq.push(head->next);
        pq.pop();

        ListNode* temp = head;

        while(!pq.empty()){

            ListNode* top = pq.top();
            if(top->next != nullptr)
                pq.push(top->next);
            pq.pop();
            temp->next = top;
            temp = temp->next;
        }

        return head;
    }
};