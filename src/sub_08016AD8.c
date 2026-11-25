void *sub_08016AB8(void);

/* Take a free node from the object pool and append it, pointing at `owner`,
   to the list at D_020279D0, bumping that list's element count. */
void *sub_08016AD8(void *owner)
{
    void *ownerCopy = owner;
    void *node = sub_08016AB8();
    u8 *pool;
    u8 *tail;
    u8 *listBase;

    if (node == 0)
        return 0;

    pool = (u8 *)0x020279D0;
    tail = *(u8 **)(pool + 8);
    listBase = pool;
    while (tail != 0)
    {
        u8 *next = *(u8 **)(tail + 4);
        if (next == 0)
            break;
        tail = next;
    }
    if (tail == 0)
        *(void **)(listBase + 8) = node;
    else
        *(void **)(tail + 4) = node;

    *(void **)node = ownerCopy;
    *(u32 *)((u8 *)node + 4) = 0;
    *(u8 *)(listBase + 1) = *(u8 *)(listBase + 1) + 1;
    return node;
}
