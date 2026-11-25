typedef struct ListNode {
    s16 value;
    u8 pad[0x2A];
    void *next;
} ListNode;

extern u32 D_02025FF0[];

/* Count the nodes in the global list (D_02025FF0+0x1870, then +0x30) whose
 * s16 value equals `value`. */
s32 sub_080144A4(s32 value) {
    s32 key = value;
    s32 count = 0;
    u32 off = 0x1870;
    void *listOwner = *(void **)((u8 *)D_02025FF0 + off);
    ListNode *node = (ListNode *)*(void **)((u8 *)listOwner + 0x30);
    if (node != 0) {
        do {
            if (node->value == key) count++;
            node = (ListNode *)node->next;
        } while (node != 0);
    }
    return count;
}
