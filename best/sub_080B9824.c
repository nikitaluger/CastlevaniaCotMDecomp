struct S_02025FF0 { u8 _0x000[0x1870]; u32 v; };
extern struct S_02025FF0 D_02025FF0;
extern void *sub_0805FAEC(void *a, s32 b);

s32 sub_080B9824(void *arg0) {
    if (((u8 *)arg0)[0x4C] == 0) return 1;
    return 0;
}

void sub_080B9834(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    void *r = sub_0805FAEC((void *)D_02025FF0.v, *(u16 *)(0x08102E10 + arg0 * 2));
    if (r != NULL) {
        *(s32 *)((u8 *)r + 0x4C) = arg1;
        *(s32 *)((u8 *)r + 0x5C) = arg2;
        *(s32 *)((u8 *)r + 0x6C) = arg3;
        *(s32 *)((u8 *)r + 0x7C) = arg4;
    }
}

void sub_080B9874(void) {
    void *r2 = *(void **)((u8 *)&D_02025FF0.v - 0x1870 + 0x30); /* placeholder */
}

void sub_080B98B8(void *arg0, u32 arg1, s32 arg2, s32 arg3) {
    u32 r5 = 0;
    s32 r4 = arg3 + 1;
    if (arg1 > 0) {
        while (r5 < arg1) {
            void *r0 = sub_0805FAEC(arg0, 0x1CF);
            if (r0 == NULL) break;
            *(s32 *)((u8 *)r0 + 0x4C) = arg2;
            *(s32 *)((u8 *)r0 + 0x5C) = r4;
            r4++;
            r5++;
        }
    }
}
