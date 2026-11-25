typedef struct {
    u8 unk0;
    u8 count;
    u8 pad[6];
    void *head;
} NodeList;
extern NodeList D_020279D0;

typedef struct Node {
    s32 key;
    struct Node *next;
} Node;
extern Node *D_02020BD4;

/* Unlinks the first node whose key equals `key` from the keyed node list,
 * updating the head/count and the current-node pointer (which falls back to the
 * list head when the removed node was the last one), then clears the node.
 * Iteration stops after that removal because node->next is read back after
 * having been zeroed. */
void sub_08016B24(u32 key) {
    NodeList *list = &D_020279D0;
    Node *node = list->head;
    Node *prev = NULL;
    if (node != NULL) {
        NodeList *listBase = list;
        u32 zero = 0;
        do {
            if (node->key != (s32)key) {
                prev = node;
            } else {
                if (node == D_02020BD4) {
                    if (node->next == NULL)
                        D_02020BD4 = listBase->head;
                    else
                        D_02020BD4 = node->next;
                }
                if (prev == NULL)
                    listBase->head = node->next;
                else
                    prev->next = node->next;
                node->key = zero;
                node->next = zero;
                listBase->count--;
            }
            node = node->next;
        } while (node != NULL);
    }
}
