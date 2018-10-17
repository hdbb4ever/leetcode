#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <exception>
#include <map>
#include <list>
#include <algorithm>
#include <time.h>
#include <string>
#include <sstream>

using namespace std;

// Definition for singly-linked list.

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
  public:
    ListNode* middleNode(ListNode* head) {
      ListNode* FastPoint, *SlowPoint;
      FastPoint = SlowPoint = head;
      // fast forward 2 but slow forward 1
      // first check fast->next is null?
      //   - yes, odd one, the current slow is mid
      //   - no, even or continue

      // Points:
      //   1) we should check ->next whether null 
      //      since we are accessing next->next
      //      otherwise segfault occurs
      // Imp:
      //   1) these two null checks can be put in the same check of while
      //     like FastPoint!=NULL && FastPoint->next!=NULL
      while(FastPoint!=NULL) {
        if (FastPoint->next == NULL)
          return SlowPoint;
        FastPoint = FastPoint->next->next;
        SlowPoint = SlowPoint->next;
      }
      // reach here, it means it's even
      return SlowPoint;
    }
};

void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}

void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}

vector<int> stringToIntegerVector(string input) {
    vector<int> output;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim)) {
        output.push_back(stoi(item));
    }
    return output;
}

ListNode* stringToListNode(string input) {
    // Generate list from the input
    vector<int> list = stringToIntegerVector(input);

    // Now convert that list into linked list
    ListNode* dummyRoot = new ListNode(0);
    ListNode* ptr = dummyRoot;
    for(int item : list) {
        ptr->next = new ListNode(item);
        ptr = ptr->next;
    }
    ptr = dummyRoot->next;
    delete dummyRoot;
    return ptr;
}

string listNodeToString(ListNode* node) {
    if (node == nullptr) {
        return "[]";
    }

    string result;
    while (node) {
        result += to_string(node->val) + ", ";
        node = node->next;
    }
    return "[" + result.substr(0, result.length() - 2) + "]";
}

int main() {
    string line;
    while (getline(cin, line)) {
        ListNode* head = stringToListNode(line);
        
        ListNode* ret = Solution().middleNode(head);

        string out = listNodeToString(ret);
        cout << out << endl;
    }
    return 0;
}
