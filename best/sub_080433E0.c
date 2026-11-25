extern void *sub_0800355C(void);
extern void sub_0800168C(void *a, s32 b, s32 c, s32 d);
extern s32 sub_08013C2C(s16);
extern void sub_0801131C(void *a, void *b, void *c);
extern void sub_08014668(void *a);
extern void sub_08011368(void *a, void *b, s32 c, s32 d);
extern void sub_080C31E0(void *a, s32 b);
extern void sub_080C31E4(void *a, void *b, s32 c);

struct S_02025FF0 {
    u8 _0[0x18A8];
    u8 byte18A8;
    u8 _1[0x18C2 - 0x18A9];
    u16 w;
};
extern struct S_02025FF0 D_02025FF0;

struct S_02021E90 { u8 _0[0x1278]; u32 f1278; u32 f127C; };
extern struct S_02021E90 D_02021E90;

extern u32 D_080CD400[];

struct O433 {
    u8 _0[0x08];
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    u8 _18[0x04];
    s16 f1C;
    u8 _1E[0x22 - 0x1E];
    u16 f22;
};

void sub_080433E0(u8 *arg0) {
    void *r7 = sub_0800355C();
    struct O433 *r5;
    s32 r8;
    s32 tmp;
    u8 *base;

    if (r7 == NULL) {
        sub_080C31E0(arg0, *(s32 *)(arg0 + 0x24));
        return;
    }
    *(u32 *)(arg0 + 0x38) = (u32)r7;
    sub_0800168C(arg0, 0, 0x48, 0);
    r5 = (struct O433 *)*(u32 *)(arg0 + 0x3C);
    if (r5 == NULL) {
        sub_080C31E0(arg0, *(s32 *)(arg0 + 0x24));
        return;
    }
    r8 = (s32)r5 + 0x34;
    r5->f1C = *(u16 *)(arg0 + 0x7C);
    *(u32 *)((u8 *)r5 + 0x18) = 1;
    r5->f08 = *(s16 *)(arg0 + 0x4C) << 16;
    r5->f0C = *(s16 *)(arg0 + 0x54) << 16;
    tmp = sub_08013C2C(r5->f1C);
    *(u16 *)&r5->f22 = tmp;
    if ((s32)(tmp << 16) < 0) {
        sub_080C31E0(arg0, *(s32 *)(arg0 + 0x24));
        return;
    }

    sub_0801131C(r7, (void *)r8, (void *)&D_080CD400[r5->f1C * 3]);

    {
        s32 mask = *(u16 *)r7 & 0xC00;
        s32 b = ((s16)r5->f22 << 6) + 0x200;
        s32 c = (r5->f22 + 8) << 12;
        *(u16 *)r7 = mask | (b | c);
    }
    *(u16 *)r7 |= D_02025FF0.w;

    *(u32 *)((u8 *)r7 + 0x1C) = 0x8000000A;

    base = (u8 *)&D_02021E90;
    { u32 k = 0x1278; *(s32 *)((u8 *)r7 + 0x14) = r5->f08 - ((*(s32 *)(base + k + ((D_02025FF0.byte18A8 + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 k = 0x127C; *(s32 *)((u8 *)r7 + 0x18) = r5->f0C - ((*(s32 *)(base + k + ((D_02025FF0.byte18A8 + 1) << 6)) + (s32)0xFFFF8000) & 0xFFFF0000); }

    r5->f10 = *(s32 *)(arg0 + 0x5C);
    r5->f14 = *(s32 *)(arg0 + 0x6C);

    sub_08014668(r7);
    sub_08011368(r7, (void *)r8, 0x0C, 1);

    *(u16 *)(arg0 + 2) |= 0x1000;
    ((u8 *)arg0)[2 * *(s16 *)(arg0 + 0x22) + 0x19] = 0;

    {
        s32 *g = (s32 *)0x08671BB0;
        sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *g);
    }
}
