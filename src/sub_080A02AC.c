struct S_02025FF0 { u8 _0x000[0x1870]; u32 v; };
extern struct S_02025FF0 gMainWorkspace;

struct Node_080A02AC {
    s16 id;
    u8 _pad[0x2C - 2];
    struct Node_080A02AC *next;
};

/* Return 1 when more than five live objects have type 0x184, else 0. */
s32 sub_080A02AC(void) {
    struct Node_080A02AC *node;
    u32 count = 0;
    node = *(struct Node_080A02AC **)((u8 *)gMainWorkspace.v + 0x30);
    if (node != NULL) {
        do {
            if (node->id == 0x184) count++;
            node = node->next;
        } while (node != NULL);
    }
    if (count > 5) return 1;
    else return 0;
}
