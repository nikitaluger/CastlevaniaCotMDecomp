/* Intrusive doubly-linked list node: +0 links back, +4 links forward. */
struct ListNode {
    struct ListNode *prev;
    struct ListNode *next;
};

/* Link `node` into the list directly after `listNode`. */
void sub_08000D10(struct ListNode *listNode, struct ListNode *node) {
    struct ListNode *next;

    next = listNode->next;
    node->next = next;
    next->prev = node;
    listNode->next = node;
    node->prev = listNode;
}
