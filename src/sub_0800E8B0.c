struct S_020278D0 {
    u8 _0x000[0x40];
    u16 v40;
    u8 _0x042[0x6];
    void *ptrs[5];
};
extern struct S_020278D0 D_020278D0;
void *sub_08001480(s32, s32);

/* Create the five status-screen objects: four numbered slots (sprite id 8)
 * plus one extra icon (sprite id 7). */
void sub_0800E8B0(s32 parent) {
    u32 i = 0;
    u8 *bb = (u8 *)&D_020278D0;
    void **p = (void **)(bb + 0x48);
    void *obj;
    do {
        obj = sub_08001480(parent, 0x1B);
        *p = obj;
        *(u8 *)((u8 *)obj + 0x3C) = 8;
        obj = *p++;
        *(u8 *)((u8 *)obj + 0x44) = (u8)i;
        i++;
    } while (i <= 3);
    D_020278D0.ptrs[4] = sub_08001480(parent, 0x1B);
    *(u8 *)((u8 *)D_020278D0.ptrs[i] + 0x3C) = 7;
}
