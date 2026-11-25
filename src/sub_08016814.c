/* Registry header at 0x020279D0: byte 0 is the next entry id, halfword +2 the
 * number of registered entries, +4 the entry-list head and +8 the free list. */
struct Registry {
    u8 nextId;
    u8 pad01;
    s16 count;
    void *head;
    void *freeList;
};

extern struct Registry D_020279D0;

/* Current number of entries in the global registry. */
s16 sub_08016814(void) {
    return D_020279D0.count;
}
