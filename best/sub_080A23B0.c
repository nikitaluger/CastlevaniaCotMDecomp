extern void sub_0800168C(u8 *, s32, s32, s32);
extern void *sub_0800355C(void *);
extern void sub_08014288(void *, void *, s32);
extern void *sub_08016190(void);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080A25D4(void);
extern u32 D_08671BB0;

struct TableEntry {
    u8 pad[0x0C];
    u16 f0C;
    u16 f0E;
    u8 rest[0x18];
};
extern struct TableEntry D_080CBDD0[];
extern u16 D_08101A70[];

void sub_080A23B0(u8 *arg0) {
    volatile u32 *child_slot;
    void *r8res;
    u8 *p;
    struct TableEntry *tablebase;
    u8 *r4;
    s32 r3;
    void *res;
    s16 idx2, idx3, idx4;
    u8 b;
    u32 zero32;
    u32 base14;
    u32 r1val;
    u8 zero8;
    u8 *fieldPtr;
    u8 *scriptPtr;

    {
        void *tmp = sub_0800355C(arg0);
        r8res = tmp;
    }
    if (r8res == 0) goto fail;
    *(u32 *)(arg0 + 0x38) = (u32)r8res;
    sub_0800168C(arg0, 0, 0x4C, 0);
    {
        void *tmp = *(void **)(arg0 + 0x3C);
        if (tmp != 0) goto main;
    }
fail:
    sub_080C31E0(arg0, *(s32 *)(arg0 + 0x24));
    return;
main:
    {
        u8 *r2 = (u8 *)r8res + 0x2A;
        u32 mask = 0xBF & *r2;
        zero32 = 0;
        *r2 = (u8)mask;
    }
    p = (u8 *)*(void **)(arg0 + 0x3C);
    child_slot = (volatile u32 *)(p + 0x48);
    sub_08014288(arg0, p, (s32)sub_080A25D4);
    *(s16 *)(p + 0x1C) = 0x54;
    *(s32 *)(p + 0x08) = zero32;
    *(s32 *)(p + 0x0C) = zero32;
    r3 = 0;
    tablebase = D_080CBDD0;
loop:
    r4 = (u8 *)D_08101A70 + r3 * 8;
    res = sub_08016190();
    *child_slot = (u32)res;
    if (res == 0) goto fail;
    zero8 = 0;
    ((u8 *)res)[1] = zero8;
    ((u8 *)*child_slot)[2] = 8;
    ((u8 *)*child_slot)[3] = 1;
    *(u16 *)((u8 *)*child_slot + 4) = tablebase[*(s16 *)(p + 0x1C)].f0C;
    *(u16 *)((u8 *)*child_slot + 6) = *(u16 *)(r4 + 0);
    *(u16 *)((u8 *)*child_slot + 8) = *(u16 *)(r4 + 2);
    *(u16 *)((u8 *)*child_slot + 10) = *(u16 *)(r4 + 4);
    *(u16 *)((u8 *)*child_slot + 12) = *(u16 *)(r4 + 6);
    *(u16 *)((u8 *)*child_slot + 14) = tablebase[*(s16 *)(p + 0x1C)].f0E;
    {
        u32 child = *child_slot++;
        *(u32 *)((u8 *)child + 0x10) = (u32)r8res;
    }
    r3 = r3 + 1;
    if (r3 == 0) goto loop;

    fieldPtr = arg0 + 0x4C;
    *fieldPtr = zero8;
    fieldPtr += 4;
    *fieldPtr = zero8;
    *(u16 *)(arg0 + 0x02) |= 0x1000;
    idx2 = *(s16 *)(arg0 + 0x22);
    *(arg0 + (idx2 << 1) + 0x19) = zero8;
    scriptPtr = arg0 + 0x18;
    sub_080C31E4(scriptPtr, arg0 + 0x22, D_08671BB0);
    idx3 = *(s16 *)(arg0 + 0x22);
    *(arg0 + (idx3 << 1) + 0x19) = *(arg0 + (idx3 << 1) + 0x19) + 1;
    idx4 = *(s16 *)(arg0 + 0x22);
    r4 = scriptPtr + (idx4 << 1);
    b = *r4;
    base14 = *(u32 *)(arg0 + 0x14);
    r1val = *(u32 *)(base14 + b * 4);
    sub_080C31E0(arg0, (s32)r1val);
}
