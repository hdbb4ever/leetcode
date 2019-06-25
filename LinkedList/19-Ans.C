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
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    if (n<=0) return head;
    /*
      Points:
        1) need to handle some corner case
         => a good idea is to use dummy header
           it can perfectly solve the corner case
           when the list only one element
           or delete the 1st element
       2) This is not the actual one pass.
          1st, get the element n away from head
          then advance both head and Noff until Noff reach end
          n + 2*(L-n)
       3) one pass can use one array to hold each nodes visited :)
     * */

    ListNode* NOffHead = head, *Curr = head;
    int i = 0;
    while (i < n) {
      // exceed max 
      if (NOffHead == NULL)
        return head;
      NOffHead = NOffHead->next;
      i++;
    }

    // just the head
    if (NOffHead == NULL)
      return head->next;

    while (NOffHead->next != NULL){
      NOffHead = NOffHead->next;
      Curr = Curr->next;
    }

    Curr->next = Curr->next->next;
    return head;
  }

  ListNode* removeNthFromEnd_imp(ListNode* head, int n) {
    if (n<=0) return head;
    ListNode* Dummy = new ListNode(0);
    Dummy->next = head;
    ListNode* NOffHead = Dummy, *Curr = Dummy;
    int i = 0;
    while (i<n) {
      NOffHead = NOffHead->next;
      i++;
    }
    
    while(NOffHead->next !=NULL) {
      NOffHead = NOffHead->next;
      Curr = Curr->next;
    }
    Curr->next = Curr->next->next;
    return Dummy->next;
  }

};
