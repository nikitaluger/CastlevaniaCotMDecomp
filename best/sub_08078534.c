extern u8 D_02023130[];

extern s32 sub_0806D518(void *, void *, void *);
extern void sub_08003A6C(void *, s32, void *);
extern void sub_08005E80(s32);
extern s32 sub_08007DD8(u32, s32);
extern void *sub_0806D2A0(s32, s32, s32, s32);
extern void sub_0806D330(void *, void *);
extern void sub_08003740(void *);
extern void sub_0806D588(void *, void *);
extern void _call_via_r1(u32, u32);
extern void _call_via_r2(u32, u32, u32);
extern s32 D_08671BB0;

struct G78534 {
    u8 pad0[0x10];
    u32 w10;
    u8 pad14[0x14D9];
    u8 b14ED;
    u8 pad14EE[0x24C];
    u8 b173A;
    u8 pad173B[0x16D];
    u8 b18A8;
    u8 pad18A9[0x19];
    u16 h18C2;
};
extern struct G78534 D_02025FF0;

static inline u32 andOne(u16 v)
{
    u32 m = 1;
    m &= v;
    return m;
}

void sub_08078534(u8 *self)
{
    s32 r2;
    u16 *r8;
    u8 *r4;
    u8 *r5;
    u8 *base20;
    void *new;
    u32 i;
    s32 fl;
    s32 rr;

    r4 = *(u8 **)(self + 0x6C);
    r8 = *(u16 **)(self + 0x38);
    r5 = r4 + 4;

    if (sub_0806D518(self, r8, r5) != 0) return;

    *(s32 *)(r5 + 0xC) += 0x4000;
    if (*(s32 *)(r5 + 0xC) > 0x80000) *(s32 *)(r5 + 0xC) = 0x80000;

    *(s32 *)(r4 + 4) += *(s32 *)(r5 + 8);
    r2 = *(s32 *)(r5 + 4) + *(s32 *)(r5 + 0xC);
    *(s32 *)(r5 + 4) = r2;

    fl = andOne(*(u16 *)(*(u8 **)(r5 + 0x2C) + 0x14));
    rr = 0;
    if (!fl) {
        rr = sub_08007DD8((D_02025FF0.b18A8 << 6) + (u32)D_02023130,
                          *(s32 *)(r4 + 4)) << 0x10;
    }
    base20 = r4 + 0x20;
    if (fl || rr != 0) {
        r4 += 0x20;
        sub_08003A6C(r4, 0, (void *)0x084D96AC);
        *(u16 *)(*(u8 **)(r5 + 0x2C) + 6) = 0xA;
        *(u16 *)(*(u8 **)(r5 + 0x2C) + 8) = 0xA;
        sub_08005E80(0x144);
        for (i = 0; i <= 7; i++) {
            new = sub_0806D2A0(*(s32 *)(self + 0x28), 0x46, 0xA, 0x12);
            if (new != NULL) {
                *(u32 *)((u8 *)new + 0x7C) = *(u32 *)(r4 + 4 - 0x20 + 0x20);
                *(u32 *)((u8 *)new + 0x8C) = *(u32 *)(r5 + 4);
                *(u32 *)((u8 *)new + 0x9C) = i;
            }
        }
        *((u8 *)((s16)*(s16 *)(self + 0x22) * 2 + (u32)self) + 0x19) = 0;
        _call_via_r2((u32)(self + 0x18), (u32)(self + 0x22), (u32)D_08671BB0);
    }

    *r8 = D_02025FF0.h18C2;
    sub_08003740(base20);
    sub_0806D588(r8, r5);
    if (D_02025FF0.b173A == 0x1C ||
        (D_02025FF0.b14ED == 0 && D_02025FF0.w10 != 0)) {
        _call_via_r1((u32)self, *(u32 *)(self + 0x24));
        return;
    }
    sub_0806D330(self, r8);
}
