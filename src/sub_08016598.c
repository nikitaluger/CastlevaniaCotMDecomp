extern void *sub_08016A54(void);
extern void *sub_08016AB8(void);
extern struct Registry D_020279D0;

struct Node {
    void *data;
    struct Node *next;
};

struct Data {
    u8 pad[2];
    u16 valueField;
    u32 lookupKey;
};

struct Registry {
    u8 pad[2];
    u16 count;
    struct Node *head;
};

/* Look up a data block by key in the global registry and update its stored
 * value. If absent, allocate a node and data pair, append it, and insert the
 * key and value. */
void *sub_08016598(void *key, s32 newValue) {
    struct Node *cursor;
    struct Node *newNode;
    void *matchKey;
    u16 storedValue;

    matchKey = key;
    storedValue = (u16)newValue;
    cursor = D_020279D0.head;

    for (;;) {
        if (cursor == NULL) goto alloc;
        if (((struct Data *)cursor->data)->lookupKey == matchKey) {
            ((struct Data *)cursor->data)->valueField = storedValue;
            return cursor->data;
        }
        if (cursor->next == NULL) break;
        cursor = cursor->next;
    }

alloc:
    newNode = sub_08016AB8();
    if (newNode == NULL) return NULL;
    newNode->data = sub_08016A54();
    if (newNode->data == NULL) return NULL;

    if (cursor == NULL) {
        D_020279D0.head = newNode;
    } else {
        cursor->next = newNode;
    }
    newNode->next = NULL;
    D_020279D0.count = D_020279D0.count + 1;
    ((struct Data *)newNode->data)->lookupKey = matchKey;
    ((struct Data *)newNode->data)->valueField = storedValue;
    return newNode->data;
}
