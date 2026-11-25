void sub_08007E24(u32);
void sub_08013AC4(void *);
s32 sub_08013B5C(void *, void *);
void sub_08013C8C(void *, void *);
void sub_080142C0(void *, void *);
void sub_08097F88(s32, void *, void *, void *);
void sub_08098338(s32, void *);
s32 sub_08098400(void);
void sub_080A3D8C(s32, void *, void *);
void sub_080A3E4C(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, u32);
extern u16 D_03000830[];
extern u32 D_0866FEB8;
extern u32 D_08671BB0[];

void sub_080A331C(u8 *arg0) {
    void *p3C;
    void *p38;
    u8 zero;
    void *p34;
    u16 v;
    u8 *p48;
    s32 funcptr;

    zero = 0;
    p38 = *(void **)(arg0 + 0x38);
    p3C = *(void **)(arg0 + 0x3C);
    p34 = (u8 *)p3C + 0x34;
    p48 = (u8 *)p3C + 0x48;
    v = (*(u16 *)p38 & 0x0FFF) | ((u16)((*(u16 *)((u8 *)p3C + 0x22) + 8) << 12));
    *(u16 *)p38 = v;
    sub_08097F88(0, p38, p3C, *(void **)((u8 *)p3C + 0x28));
    sub_08097F88(2, p38, p3C, *(void **)(p48 + 0x50));
    sub_080142C0(arg0, *(void **)((u8 *)p3C + 0x28));
    sub_080142C0(arg0, *(void **)(p48 + 0x50));
    sub_080142C0(arg0, *(void **)(p48 + 0x54));
    sub_080142C0(arg0, *(void **)(p48 + 0x58));

    if (*(u16 *)p3C & 1) {
        u32 *p;
        u8 *p18;
        u8 byte;
        s32 idx;
        sub_08013AC4(arg0);
        sub_08007E24(0xB6);
        *(u8 *)(*(u8 **)((u8 *)p3C + 0x28) + 1) = zero;
        *(u8 *)(*(u8 **)(p48 + 0x50) + 1) = zero;
        *(u8 *)(*(u8 **)(p48 + 0x54) + 1) = zero;
        *(u8 *)(*(u8 **)(p48 + 0x58) + 1) = zero;
        {
            u8 *base;
            base = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
            *(u8 *)(base + 0x19) = zero;
        }
        p = (u32 *)0x08671BB0;
        p18 = arg0 + 0x18;
        sub_080C31E4(p18, arg0 + 0x22, *p);
        {
            u8 *base;
            base = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
            *(u8 *)(base + 0x19) = *(u8 *)(base + 0x19) + 1;
        }
        idx = (s32)(s16)(*(s16 *)(arg0 + 0x22)) * 2;
        p18 += idx;
        byte = *p18;
        funcptr = *(s32 *)((u32)(byte * 4) + *(u32 *)(arg0 + 0x14));
        sub_080C31E0((s32)arg0, funcptr);
        return;
    }

    if (sub_08098400() == 0) {
        D_03000830[2] = 0x3F40;
        D_03000830[3] = 0x060A;
    }

    if (sub_08013B5C(p38, p3C) == 0) {
        u8 *p18;
        u8 byte;
        s32 idx;
        sub_080A3E4C(arg0, p48);
        *(u32 *)(arg0 + 0x14) = (u32)&D_0866FEB8;
        *(u16 *)(arg0 + 0x22) = *(u16 *)(arg0 + 0x22) + 1;
        {
            u8 *base;
            base = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
            *(u8 *)(base + 0x19) = *(u8 *)(base + 0x19) + 1;
        }
        idx = (s32)(s16)(*(s16 *)(arg0 + 0x22)) * 2;
        p18 = arg0;
        p18 += 0x18;
        p18 += idx;
        byte = *p18;
        sub_080C31E0((s32)arg0, *(s32 *)((u32)(byte * 4) + *(u32 *)(arg0 + 0x14)));
        *(u16 *)(arg0 + 0x22) = *(u16 *)(arg0 + 0x22) - 1;
    }
    sub_080A3D8C((s32)p34, p3C, p48);
    sub_08098338(1, p38);
    sub_08013C8C(arg0, p38);
}
