#include<bits/stdc++.h>
using namespace std;


// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};


class Solution {
public:
    Node* copyRandomList(Node* head) {
        
        unordered_map<Node*, Node*> m;
        Node *temp = head;
        Node *head2 = NULL, *temp2 = NULL, *node;
        
        while(temp != NULL){
            
            if(head2 == NULL){
                head2 = new Node(temp->val);
                m[temp] = head2;
                temp2 = head2;
                if(temp->random && !m.count(temp->random)){
                    head2->random = new Node(temp->random->val);
                    m[temp->random] = head2->random;
                }
                else if(temp->random){
                    head2->random = m[temp->random];
                }
            }
            else{
                if(!m.count(temp)){
                    node = new Node(temp->val);
                    m[temp] = node;
                    temp2->next = node;
                }
                else{
                    temp2->next = m[temp];
                }
                
                if(temp->random){
                    if(m[temp->random])
                        temp2->next->random = m[temp->random];
                    else{
                        Node* randNode = new Node(temp->random->val);
                        temp2->next->random = randNode;
                        m[temp->random] = randNode;
                    }
                }
                temp2 = temp2->next;    
            }
            temp = temp->next;
        }
        
        return head2;
    }
};