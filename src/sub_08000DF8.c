void *sub_08000DC4(void **);            /* pop a node from the free list */
void sub_08000DE0(void **, void *);      /* append a node to a list */

/* Pool of linked nodes: a free list plus 4x2 lists of in-use nodes. */
struct Pool {
    void *freeList;
    void *lists[4][2];
};
extern struct Pool D_020223B8;

/* Allocate a node from the pool, store the three payload words in it and
 * append it to the list selected by arg0 (low 2 bits) and bits 16-17; returns
 * -1 when the pool is exhausted. */
s32 sub_08000DF8(u32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u32 typeIndex = arg0 & 3;
    u32 bankIndex = (arg0 & 0x30000) >> 16;
    void *node = sub_08000DC4(&D_020223B8.freeList);
    if (node != NULL) {
        *(s32 *)node = arg1;
        *(s32 *)((u8 *)node + 4) = arg2;
        *(s32 *)((u8 *)node + 8) = arg3;
        sub_08000DE0(&D_020223B8.lists[typeIndex][bankIndex], node);
        return 0;
    }
    return -1;
}
