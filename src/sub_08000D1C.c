struct ListNode {
    struct ListNode *next;
    struct ListNode *prev;
};

/* Point the list head at node and make node a one-element circular list. */
void sub_08000D1C(struct ListNode **head, struct ListNode *node) {
    *head = node;
    node->next = node;
    node->prev = node;
}
