struct ObjectPoolEntry { u32 *ptr; u8 pad[0x1C]; };
extern struct ObjectPoolEntry gMainWorkspace[];

void *sub_0805FAEC(s32, s32);

/* Allocate an object of type 0x1E5 from the pool in gMainWorkspace[0xC4] and copy
 * the four game parameters into its fields at +0x4C..+0x56. Returns NULL when
 * the pool is exhausted. */
void *sub_0805E6A8(s32 arg0, s32 arg1, u16 arg2, u16 arg3) {
    void *r;
    void *ptr;
    u8 *q;
    ptr = gMainWorkspace[0xC4].ptr;
    r = sub_0805FAEC((s32)ptr, 0x1E5);
    if (r == 0) return 0;
    q = (u8 *)r + 0x4C;
    *(s32 *)q = arg0;
    *(s32 *)(q + 4) = arg1;
    *(u16 *)(q + 8) = arg2;
    *(u16 *)(q + 10) = arg3;
    return r;
}
