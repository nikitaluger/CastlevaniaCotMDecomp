extern void *allocEffectPart(void);
extern void sub_08003A6C(void *, s32, void *);
extern void sub_0806D2D0(void *);
extern s16 sub_0806D62C(u16, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern u8 gGameStatus[];
extern u8 gMainWorkspace[];
extern s32 D_02027718;
extern u8 gMainObjTimerCallback[];

static inline u32 bitOne(u8 v) {
    u32 m = 1;
    m &= v;
    return m;
}

void sub_0807F320(u8 *arg0) {
    u8 *r7 = *(u8 **)(arg0 + 0x6C);
    u8 *r4 = *(u8 **)(arg0 + 0x38);
    u8 *r5 = r7 + 4;
    u8 *r9 = gMainWorkspace;
    u8 *r8 = gGameStatus;
    u8 *obj;
    u32 r1v;
    s16 idx;
    u8 spbuf[8];
    u8 *a18;

    obj = allocEffectPart();
    *(u8 **)(r5 + 0x2C) = obj;
    if (0 == obj) {
        sub_0806D2D0(arg0);
    } else {
        *(u32 *)(r5 + 0x30) = 0;
        *(u32 *)(r5 + 0x34) = 0;
        *(u32 *)(r5 + 0x38) = 0;
        *(u32 *)(r5 + 0x3C) = 0;
        obj[1] = bitOne(r9[0x1510]);
        (*(u8 **)(r5 + 0x2C))[2] = 2;
        (*(u8 **)(r5 + 0x2C))[3] = 8;
        *(u16 *)(*(u8 **)(r5 + 0x2C) + 4) = r8[0x304];
        *(u16 *)(*(u8 **)(r5 + 0x2C) + 6) = 0x0A;
        *(u16 *)(*(u8 **)(r5 + 0x2C) + 8) = 4;
        *(u16 *)(*(u8 **)(r5 + 0x2C) + 0xA) = 0;
        *(u16 *)(*(u8 **)(r5 + 0x2C) + 0xC) = 0;
        *(u16 *)(*(u8 **)(r5 + 0x2C) + 0xE) = sub_0806D62C(*(u16 *)(r8 + 0x2E2), 0x64);
        *(u16 *)(*(u8 **)(r5 + 0x2C) + 0x16) = 0x1E;
        *(u16 *)(*(u8 **)(r5 + 0x2C) + 0x18) = 0x67;
        *(u8 **)(*(u8 **)(r5 + 0x2C) + 0x10) = r4;
        *(u32 *)(r5 + 0x18) = *(u32 *)(arg0 + 0x24);
        *(u32 *)(arg0 + 0x24) = 0x0808449D;
        *(u32 *)(r4 + 0x24) = 0x084EA8E4;
        sub_08003A6C(r7 + 0x20, 0, (void *)0x084EA9A4);
        *(u32 *)((*(u8 **)(arg0 + 0x6C)) + 4) = *(u32 *)(arg0 + 0x7C);
        *(u32 *)(r5 + 4) = *(u32 *)(arg0 + 0x8C) + 0xFFFD0000;
        if (*(s32 *)(r7 + 4) > D_02027718) {
            *(u16 *)(r4 + 2) |= 0x10;
            r1v = 0xFFF80000;
        } else {
            *(u16 *)(r4 + 2) &= 0xFFEF;
            r1v = 0x80000;
        }
        *(u32 *)(r7 + 4) += r1v;
        *(u32 *)(r5 + 8) = r1v;
        *(u32 *)(r5 + 0xC) = 0;
        idx = *(s16 *)(arg0 + 0x22);
        *(u8 *)((u32)arg0 + idx * 2 + 0x19) = 0;
        a18 = arg0 + 0x18;
        *(u8 **)spbuf = a18;
        { u8 *__fence_a18; do { __fence_a18 = a18; } while (0); sub_080C31E4(*(u8 **)spbuf, __fence_a18 + 0x0A, *(void **)0x08671BB0); }
        idx = *(s16 *)(arg0 + 0x22);
        *(u8 *)((u32)arg0 + idx * 2 + 0x19) += 1;
        idx = *(s16 *)(arg0 + 0x22);
        sub_080C31E0(arg0, *(void **)(*(u8 *)(*(u8 **)spbuf + (idx << 1)) * 4 + *(u32 *)(arg0 + 0x14)));
    }
}
