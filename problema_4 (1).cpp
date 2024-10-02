/**
 * Definition for singly-linked list->
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
/**
 * Definition for a binary tree node->
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

    bool funcion(ListNode* head, TreeNode* root){
        if(head->next!=nullptr) {
            if (root->right->val == head->next->val or root->left->val == head->next->val) {
                return funcion(head->next, root->right) or funcion(head->next, root->left);
            } else {
                return false;
            }
        }
        else{
            return true;
        }
    }

class Solution {
public:
    bool isSubPath(ListNode* head, TreeNode* root) {
    if(root !=nullptr){
    if(root->val == head->val){
        return isSubPath(head,root);
        return false;
    }
    else{
        return isSubPath(head,root->right) and isSubPath(head,root->left);
    }
    }
    return false;
    }
};
