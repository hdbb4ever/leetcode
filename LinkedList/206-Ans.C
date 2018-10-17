/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
    /**
       node1 -> node2 -> node3
     ==>
       tmp = node1.next (node2)
       node1.next = new_head
       new_head = node1
       continue on node2
    **/    
      ListNode* new_head = NULL;
      while (head != NULL) {
        ListNode* tmp = head->next;
        head->next = new_head;
        new_head = head;
        head = tmp;
      }
      head = new_head;
      return head;
    }

    ListNode* reverseList_rec(ListNode* head) {
    /**
       node1 -> node2 -> node3
     ==>
       func(head):
         if head == null return null
         if head->next != null
           t = func(head->next)
           head->next = null
           t->next = head
           return t;
         else
           return head
         
     ==> Points:
         1) above is wrong, shouldn't use t->next
            since t stands for the current header
            like 1->2->3
              head is 1
              head->next is 2
              t is 3->2->null
            !!!
            so it should be
              head->next->next = head
          2) the space complexicity is O(n)
             implicit stack space
    **/    
      if (head == NULL)
        return head;
      if (head->next == NULL)
        return head;
      else
      {
        ListNode* t = reverseList_rec(head->next); // typo to put head here!
        head->next->next = head; // head's next is put in the end of new list t
        head->next = NULL; // now head is at the end
        return t;
      }
    }


};
