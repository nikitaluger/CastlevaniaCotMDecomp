void *sub_0805FAEC(void *parent, s32 type);

/* Spawn a type-0x1A7 auxiliary object tagged with `index` in the byte at
 * +0x4C; returns NULL when no spawn slot is available. */
void *sub_080B0614(void *parent, u8 index)
{
    void *obj = sub_0805FAEC(parent, 0x1A7);
    if (obj == 0)
        return 0;
    *(u8 *)((u8 *)obj + 0x4C) = index;
    return obj;
}
