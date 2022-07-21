#include<bits/stdc++.h>
using namespace std;

/*Definition for singly-linked list.*/
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        
        if(left == right)
            return head;
        
        ListNode *prev = nullptr, *temp = head;
        int idx = 1;
        while(idx < left){
            prev = temp;
            temp = temp->next;
            idx++;
        }
        
        ListNode *curr = temp, *prev2 = nullptr;
        idx = left;
        while(idx <= right){
            ListNode* temp = curr->next;
            curr->next = prev2;
            prev2 = curr;
            curr = temp;
            idx++;
        }
        temp->next = curr;
        if(prev != nullptr)
            prev->next = prev2;
        else
            head = prev2;
        
        return head;
    }
};