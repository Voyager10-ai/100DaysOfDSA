class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0);
        dummy.next = head;
        
        ListNode* first = &dummy;
        ListNode* second = &dummy;
        
        // Advance first pointer by n + 1 steps
        for (int i = 1; i <= n + 1; i++) {
            first = first->next;
        }
        
        // Move both pointers until first reaches the end
        while (first != nullptr) {
            first = first->next;
            second = second->next;
        }
        
        // Remove the nth node
        ListNode* nodeToDelete = second->next;
        second->next = second->next->next;
        
        // Optional: delete nodeToDelete to prevent memory leak
        // delete nodeToDelete;
        
        return dummy.next;
    }
};
