void *sub_08001480(s32, s32);

/* Allocate a kind-0x14 object as a child of `parent`, mark it active and store
 * two 16-bit parameters at +0x44 and +0x4C; returns NULL if allocation failed. */
void *sub_0805FC0C(s32 parent, u16 paramA, u16 paramB) {
    void *obj = sub_08001480(parent, 0x14);
    if (obj == NULL) {
        return NULL;
    }
    *(s8 *)((u8 *)obj + 0x3C) = 1;
    *(u16 *)((u8 *)obj + 0x44) = paramA;
    *(u16 *)((u8 *)obj + 0x44 + 8) = paramB;
    return obj;
}
