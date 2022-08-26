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
        Node *head2 = NULL, *temp2 = NULL, *node, *prev = NULL;
        
        while(temp != NULL){
            
            if(head2 == NULL){
                head2 = new Node(temp->val);
                m[temp] = head2;
            }
            else{
                if(!m.count(temp)){
                    node = new Node(temp->val);
                    m[temp] = node;
                    prev->next = node;
                }
                else{
                    prev->next = m[temp];
                }
                    
            }
            
            if(temp->random){
                if(m[temp->random])
                    m[temp]->random = m[temp->random];
                else{
                    Node* randNode = new Node(temp->random->val);
                    m[temp]->random = randNode;
                    m[temp->random] = randNode;
                }
            }
            prev = m[temp];
            temp = temp->next;
            
        }
        return head2;
    }
};