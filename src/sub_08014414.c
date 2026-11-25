/* Reassign every node of the source list to the global group pointer, append
 * that list to the group's list, then clear the source list head. `scratch`
 * holds the global base first and the next-node link in the append loop. */
extern u32 D_02025FF0[];

void sub_08014414(void *sourceList) {
    u32 scratch;
    u32 offset;
    void *head = *(void **)((u8 *)sourceList + 0x30);
    void *first;
    void *group;
    void *cur;
    void *cursor;
    if (head == 0) return;
    first = head;
    cur = first;
    scratch = (u32)D_02025FF0;
    offset = 0x1870;
    group = *(void **)(scratch + offset);
    do {
        *(void **)((u8 *)cur + 0x28) = group;
        cur = *(void **)((u8 *)cur + 0x2C);
    } while (cur != 0);
    group = *(void **)(scratch + 0x1870);
    cursor = *(void **)((u8 *)group + 0x30);
    if (cursor != 0) {
        for (;;) {
            scratch = *(u32 *)((u8 *)cursor + 0x2C);
            if (scratch == 0) {
                *(void **)((u8 *)cursor + 0x2C) = *(void **)((u8 *)sourceList + 0x30);
                *(void **)((u8 *)sourceList + 0x30) = (void *)scratch;
                return;
            }
            cursor = (void *)scratch;
        }
    }
}
