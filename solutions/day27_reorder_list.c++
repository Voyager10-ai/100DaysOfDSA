class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next) return;

        // 1. Find the middle of the linked list
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // 2. Reverse the second half of the list
        ListNode* prev = nullptr;
        ListNode* curr = slow->next;
        slow->next = nullptr;
        while (curr) {
            ListNode* nextTemp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextTemp;
        }

        // 3. Merge the two halves
        ListNode* l1 = head;
        ListNode* l2 = prev;
        while (l2) {
            ListNode* next1 = l1->next;
            ListNode* next2 = l2->next;
            
            l1->next = l2;
            l2->next = next1;
            
            l1 = next1;
            l2 = next2;
        }
    }
};
