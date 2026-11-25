struct Obj {
    u8 _0[0x22];
    s16 field22;
    u8 _1[0x38-0x24];
    void *field38;
    void *field3C;
};
extern u16 D_080CF9B0[];
extern u32 D_08671BB0;
extern void sub_08011368(s32, void*, s32, s32);
extern s32 sub_08014990(s32);
extern void *sub_0804CBA0(s32, s32, u16, s32, s32);
extern void sub_080C31E4(void*, void*, s32);

void sub_0804C2F8(struct Obj *arg0) {
    s32 r6 = (s32)arg0->field38;
    void *r5 = arg0->field3C;
    void *r4 = (u8*)r5 + 0x34;
    void *r7 = (u8*)r5 + 0x48;
    u16 r4v;
    sub_08011368(r6, r4, 5, 1);
    if (*((u8*)r4 + 1) == 3 && *(s32*)((u8*)r4 + 4) == 1) {
        if (sub_08014990(r6) < 0) {
            u32 base = (u32)D_080CF9B0;
            s32 idx = 6 - *(s16*)((u8*)r7 + 4);
            u16 val = *(u16*)(base + idx * 2);
            r4v = (u16)(val + 0x4000);
            sub_0804CBA0(*(s32*)((u8*)r5+8) + 0xFFE80000, *(s32*)((u8*)r5+0xC) + 0xC0000, r4v, 0x30000, *(s16*)((u8*)r5 + 0x1C));
        } else {
            u32 base = (u32)D_080CF9B0;
            s32 idx = 6 - *(s16*)((u8*)r7 + 4);
            u16 val = *(u16*)(base + idx * 2);
            r4v = (u16)(0x4000 - val);
            sub_0804CBA0(*(s32*)((u8*)r5+8) + 0x180000, *(s32*)((u8*)r5+0xC) + 0xC0000, r4v, 0x30000, *(s16*)((u8*)r5 + 0x1C));
        }
        *(s16*)((u8*)r7 + 4) = *(s16*)((u8*)r7 + 4) - 1;
    }
    if (*(s16*)((u8*)r7 + 4) <= 0) {
        u8 *p = (u8*)arg0 + arg0->field22 * 2;
        p[0x19] = 0;
        { u32 *pd = &D_08671BB0;
          sub_080C31E4((u8*)arg0 + 0x18, (u8*)arg0 + 0x22, *pd); }
    }
}
