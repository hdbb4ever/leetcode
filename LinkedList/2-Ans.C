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
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    /*
       1) get both numbers
       2) construct list with the number
       Question? how to deal with memory leak? auto_ptr
 
       Points: 
        1) the naive idea to get the number can't work well
           the test cases are using big number, even with 
           unsigned long long, the times can't fold
           So have to back to see the problem again.
        2) my solution can work, but the official solution is better,
           it takes left null linked list as zero, so 
           the l1,l2 loop and left loop can be combined.
        3) it's also a good idea to provide a dummy head, then 
           return dummy.next out of the function (seems not practical? extra space?)
           My codes to setup the head first, but it doesn't with dummy head
           !!! dummy.next as head, curr as the tail, we don't require to use head all
           the time, thinking more on dummy haha.
        4) Please remember to handle the final carry
           it should be carried out one more number if set.
    */
    ListNode* head = NULL;
    if (l1 == NULL) return l2;
    if (l2 == NULL) return l1;

    int N1 = l1->val;
    int N2 = l2->val;
    int carry = 0;
    int Sum = N1+N2;
    if (Sum>=10) carry = 1;
    int N = Sum%10;
    std::auto_ptr<ListNode> n(new ListNode(N));
    head = n.release();
    ListNode* tail = head;
    l1=l1->next;
    l2=l2->next;

    while(l1 != NULL && l2 != NULL) {
      N1 = l1->val;
      N2 = l2->val;
      Sum = N1+N2+carry;
      if (Sum>=10) carry = 1;
      else carry = 0;
      N = Sum%10;
      std::auto_ptr<ListNode> n(new ListNode(N));
      tail->next = n.release();
      tail = tail->next;
      l1 = l1->next;
      l2 = l2->next;
    }

    ListNode* left = NULL;
    if (l1!=NULL) left = l1;
    else if (l2!=NULL) left = l2;

    while (left != NULL) {
      N1 = left->val;
      Sum = N1+carry;
      if (Sum>=10) carry = 1;
      else carry = 0;
      N = Sum%10;
      std::auto_ptr<ListNode> n(new ListNode(N));
      tail->next = n.release();
      tail = tail->next;
      left = left->next;
    }

    if (carry == 1) {
      std::auto_ptr<ListNode> n(new ListNode(1));
      tail->next = n.release();
      tail = tail->next;         
    }

    return head;
  }

  ListNode* addTwoNumbers_imp(ListNode* l1, ListNode* l2) {
    if (l1 == NULL) return l2;
    if (l2 == NULL) return l1;

    ListNode* Dummy = new ListNode(0);
    ListNode* Tail = Dummy;

    int Carry = 0;
       
    while(l1 != NULL || l2 != NULL) {
      int N1 = l1?l1->val:0;
      int N2 = l2?l2->val:0;
      int Sum = N1+N2+Carry;
      if (Sum>=10) Carry = 1;
      else Carry = 0;
      int N = Sum%10;
      ListNode* n = new ListNode(N);
      Tail->next = n;
      Tail = Tail->next;
      l1 = l1?l1->next:l1;
      l2 = l2?l2->next:l2;
    }

    if (Carry == 1) {
      ListNode* n = new ListNode(1);
      Tail->next = n;
      Tail = Tail->next;
    }

    return Dummy->next;
  }
};

/*
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
  unsigned long long N1 = getNumber(l1);
  unsigned long long N2 = getNumber(l2);
  unsigned long long Sum = N1 + N2;

  unsigned long long LeftNums = Sum;
  if (LeftNums == 0) {
    std::auto_ptr<ListNode> n(new ListNode(0));
    return n.release();
  }

  int N = LeftNums % 10;
  LeftNums /= 10; 
  std::auto_ptr<ListNode> n(new ListNode(N));
  ListNode* head = n.release();
  ListNode* tail = head;
  while (LeftNums != 0) {
    N = LeftNums % 10;
    LeftNums /= 10;
    std::auto_ptr<ListNode> n(new ListNode(N));
    ListNode* t = n.release();
    tail->next = t;
    tail = t;
  }
  return head;
}
unsigned long long getNumber(ListNode* head){
  unsigned long long Times = 1;
  unsigned long long RetValue = 0;
  while (head != NULL) {
    RetValue += head->val*Times;
    Times *= 10;
    head = head->next;
  }
  return RetValue;
}
 * */
