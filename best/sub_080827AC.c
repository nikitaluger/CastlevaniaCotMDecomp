extern void *sub_08016190(void);
extern void sub_0806D2D0(void *a);
extern s16 sub_0806D62C(u16, s32);
extern void sub_08003A6C(void *a, s32 b, void *c);
extern s32 sub_08072280(s32 a, s32 b, s32 c, s32 d);
extern void sub_080722E0(void *a, u8 b);
extern s32 sub_080C36E4(s32 a, s32 b);
extern void sub_080C31E0(void *a, void *b);
extern void sub_080C31E4(void *a, void *b, void *c);

struct S_02025FF0 {
    u8 _0[0x14EF];
    u8 b14EF;
    u8 _1[0x1510 - 0x14F0];
    u8 b1510;
    u8 _2[0x1728 - 0x1511];
    u32 f1728;
    u32 f172C;
};
extern struct S_02025FF0 D_02025FF0;
extern u8 D_02025368[];
extern s32 D_080E5D20[];
extern s32 D_080E5DE0[];

struct Child78 {
    u8 f0, f1, f2, f3;
    u16 f4, f6, f8, fA, fC, fE;
    u32 f10;
    u8 _14[2];
    u16 f16, f18;
};
struct Parent5 {
    u8 _0[4];
    u32 f04;
    u8 _1[0x18-0x08];
    u32 f18;
    u8 _2[0x2C-0x1C];
    struct Child78 *f2C;
    u32 f30, f34, f38, f3C;
};

void sub_080827AC(u8 *arg0)
{
    u8 *base = *(u8 **)(arg0 + 0x6C);
    struct Parent5 *r7 = (struct Parent5 *)(base + 4);
    u8 *r9 = *(u8 **)(arg0 + 0x38);
    u8 *d25368 = D_02025368;
    struct Child78 *r3 = sub_08016190();
    s32 *tbl;
    s32 idx;
    s32 r8v;
    s32 r6v;
    s32 a2;
    s32 a3;
    s32 *g;
    u8 *p18;

    r7->f2C = r3;
    if (r3 == NULL) {
        sub_0806D2D0(arg0);
        return;
    }
    r7->f30 = 0;
    r7->f34 = 0;
    r7->f38 = 0;
    r7->f3C = 0;

    r3->f1 = D_02025FF0.b1510 & 1;
    r7->f2C->f2 = 2;
    r7->f2C->f3 = 8;
    r7->f2C->f4 = d25368[0xC1 << 2];
    r7->f2C->f6 = 0x0E;
    r7->f2C->f8 = 0x0E;
    r7->f2C->fA = 0;
    r7->f2C->fC = 0;
    r7->f2C->fE = sub_0806D62C(*(u16 *)(d25368 + 0x2E2), 0x54);
    r7->f2C->f16 = 0x1E;
    r7->f2C->f18 = 0x78;
    r7->f2C->f10 = (u32)r9;

    r7->f18 = *(u32 *)(arg0 + 0x24);
    *(u32 *)(arg0 + 0x24) = 0x0808449D;
    *(u32 *)(r9 + 0x24) = 0x084F6938;

    sub_08003A6C(base + 0x20, 0, (void *)0x084F6988);

    tbl = D_080E5D20;
    idx = sub_080C36E4(*(s32 *)(arg0 + 0x9C), 0x18);
    r8v = tbl[idx * 2];
    *(s32 *)(r9 + 0x14) = r8v;
    idx = sub_080C36E4(*(s32 *)(arg0 + 0x9C), 0x18);
    tbl++;
    r6v = tbl[idx * 2];
    *(s32 *)(r9 + 0x18) = r6v;

    tbl = D_080E5DE0;
    idx = sub_080C36E4(*(s32 *)(arg0 + 0x9C), 7);
    a2 = tbl[idx * 2];
    tbl++;
    a3 = tbl[idx * 2];
    sub_080722E0(r7, (u8)sub_08072280(r8v, r6v, a2, a3));

    *(s32 *)((u8 *)r7 + 8) <<= 3;
    *(s32 *)((u8 *)r7 + 0xC) <<= 3;

    *((u8 *)((s16)*(s16 *)(arg0 + 0x22) * 2 + (u32)arg0) + 0x19) = 0;
    g = (s32 *)0x08671BB0;
    p18 = arg0 + 0x18;
    sub_080C31E4(p18, arg0 + 0x22, (void *)*g);
    {
        u8 *p = (u8 *)((s16)*(s16 *)(arg0 + 0x22) * 2 + (u32)arg0);
        *(u8 *)(p + 0x19) = (u8)(*(u8 *)(p + 0x19) + 1);
    }
    {
        u8 *p = p18 + (s16)*(s16 *)(arg0 + 0x22) * 2;
        sub_080C31E0(arg0, *(void **)((u32)(*p) * 4 + *(u32 *)(arg0 + 0x14)));
    }
}
