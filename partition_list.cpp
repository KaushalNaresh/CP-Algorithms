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
    
    ListNode* partition(ListNode* head, int x) {
        
        ListNode *before = new ListNode(0), *after = new ListNode(0), *afterNode = after, *beforeNode = before; 
        
        while(head){
            if(head->val < x){
                before->next = head;
                before = before->next;
            }
            else{
                after->next = head;
                after = after->next;
            }
            head = head->next;
        }
        
        after->next = nullptr;
        before->next = afterNode->next;
        
        return beforeNode->next;
    }
};