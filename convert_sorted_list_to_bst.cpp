#include<bits/stdc++.h>
using namespace std;

/*
 * Definition for singly-linked list.
 **/
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/*
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution {
public:

    pair<ListNode*, ListNode*> getMid(ListNode* strt, ListNode* end){

        ListNode *slow = strt, *fast = strt, *prev = nullptr;

        while(slow != end && fast != end && fast->next != end){
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        return {slow, prev};
    }

    TreeNode* utilFunc(ListNode* strt, ListNode* end){

        // cout<<strt->val<<" "<<end->val<<endl;

        if(strt == nullptr || end == nullptr)
            return nullptr;

        if(strt == end)
            return new TreeNode(strt->val);

        pair<ListNode*, ListNode*> p = getMid(strt, end);
        ListNode* mid = p.first;
        ListNode* prev = p.second;

        // cout<<mid->val<<"MID"<<endl;
        if(prev) cout<<prev->val<<"PREV"<<endl;

        TreeNode* leftNode = utilFunc(strt, prev);
        TreeNode* rightNode = utilFunc(mid->next, end);

        TreeNode* root = new TreeNode(mid->val);

        root->left = leftNode;
        root->right = rightNode;

        return root;
    }

    TreeNode* sortedListToBST(ListNode* head) {
        
        ListNode *end, *strt;

        if(head == NULL)
            return NULL;

        end = head, strt = head;
        while(end->next)
            end = end->next;

        return utilFunc(strt, end);
    }
};

//-10,-3,0,5,9