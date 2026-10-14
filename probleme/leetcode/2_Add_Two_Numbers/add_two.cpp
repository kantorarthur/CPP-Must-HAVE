#include <cstdint>

using namespace std;

  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        uint8_t l1_size{};
        uint8_t l2_size{};
        ListNode* l1_head = l1;
        ListNode* l2_head = l2;
        while(l1_head)
        {
            ++l1_size;
            l1_head = l1_head -> next;
        }
        while(l2_head)
        {
            ++l2_size;
            l2_head = l2_head -> next;
        }

        if(l1_size >= l2_size)
        {
            ListNode* l1_cpy = l1;
            while(l2)
            {
                l1 -> val += l2 -> val;
                if( l1 -> val >= 10 )
                {
                    uint8_t val_to_add = l1 -> val / 10;
                    l1 -> val = (l1 -> val) % 10;
                    if(l1 -> next)
                        (l1 -> next) -> val += val_to_add;
                    else
                        l1 -> next = new ListNode(val_to_add);

                }
                l1 = l1 -> next;
                l2 = l2 -> next;
            }
            while(l1)
            {
                if(l1 -> val >= 10)
                {
                    uint8_t val_to_add = l1 -> val / 10;
                    l1 -> val = (l1 -> val) % 10;
                    if(l1 -> next)
                        (l1 -> next) -> val += val_to_add;
                    else
                        l1 -> next = new ListNode(val_to_add);

                }
                l1 = l1 -> next;
            }
            return l1_cpy;
        }
        else
        {
            ListNode* l2_cpy = l2;
            while(l1)
            {
                l2 -> val += l1 -> val;
                if( l2 -> val >= 10 )
                {
                    uint8_t val_to_add = (l2 -> val) / 10;
                    l2 -> val = (l2 -> val) % 10;
                    if(l2 -> next)
                        (l2 -> next) -> val += val_to_add;
                    else
                        l2 -> next = new ListNode(val_to_add);
                }
                l1 = l1 -> next;
                l2 = l2 -> next;
            }
            while(l2)
            {
                if(l2 -> val >= 10)
                {
                    uint8_t val_to_add = l2 -> val / 10;
                    l2 -> val = (l2 -> val) % 10;
                    if(l2 -> next)
                        (l2 -> next) -> val += val_to_add;
                    else
                        l2 -> next = new ListNode(val_to_add);
                }
                l2 = l2 -> next;
            }
            return l2_cpy;
        }
        return l1;
        
    }
};
