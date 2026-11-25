extern void *sub_08016190(void);
extern void *sub_08016A2C(void);
extern void sub_0806D2D0(void *);
extern void sub_0806D588(void *, void *);
extern s32 sub_0806D62C(u16, s32);
extern void sub_080722E0(void *, u8);
extern void sub_08003A6C(s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void sub_080718F4(void);
struct F0 {
    u8 _0[0x1510]; u8 f1510;
    u8 _1511[0x174C-0x1511]; u32 f174C;
    u32 f1750;
    u8 _1754[0x18C2-0x1754]; u16 f18C2;
};
struct S68 { u8 _0[0x2DE]; u16 f2DE; };
struct R { u8 f0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; u32 f10; u8 _14[2]; u16 f16; u16 f18; u32 f1A; u32 f24; };
struct C4 { u32 f0; u32 f4; u32 f8; u32 fC; u32 f10; u32 f14; u32 f18; u32 f1C; u32 f20; u32 f24; u8 _28[0x3C-0x28]; struct R *f3C; u32 f40; };
struct C { u32 f0; u32 f4; u32 f8; u32 fC; u32 f10; u32 f14; u32 f18; u32 f1C; u32 f20; u8 f24; u8 f25; u8 _26[0x30-0x26]; u32 f30; u8 _34[0x48-0x34]; u8 f48; };
struct P38 { u16 f0; u8 _2[2]; u16 f4; u16 f6; u16 f8; u16 fA; u8 _C[0x1C-0xC]; u32 f1C; u32 f20; u32 f24; };
extern struct F0 D_02025FF0;
extern struct S68 D_02025368;
extern u8 D_080E0C90[];
extern s32 D_08671BB0[];
extern s32 D_08671BD0[];

void sub_08070290(void *arg0)
{
    struct C *p6C; struct C4 *p6C4; struct P38 *p38; void *r2;
    s32 r10; s32 r9; u8 b; u8 f1v;

    p6C = *(struct C **)((u8 *)arg0 + 0x6C);
    p6C4 = (struct C4 *)((u8 *)p6C + 4);
    p38 = *(struct P38 **)((u8 *)arg0 + 0x38);
    r2 = sub_08016190();
    p6C4->f3C = r2;
    if (r2 == NULL) {
        sub_0806D2D0(arg0);
        return;
    }

    f1v = (r10 = 5) & D_02025FF0.f1510;
    r9 = 0;
    ((struct R *)r2)->f1 = f1v;
    p6C4->f3C->f2 = 2;
    p6C4->f3C->f3 = 8;
    p6C4->f3C->f4 = r9;
    p6C4->f3C->f6 = 8;
    p6C4->f3C->f8 = 8;
    p6C4->f3C->fA = r9;
    p6C4->f3C->fC = r9;
    p6C4->f3C->fE = sub_0806D62C(D_02025368.f2DE, 100);
    p6C4->f3C->f10 = (u32)p38;
    p6C4->f3C->f16 = r10;
    p6C4->f3C->f18 = 0x7B;
    p6C4->f18 = *(u32 *)((u8 *)arg0 + 0x24);
    *(u32 *)((u8 *)arg0 + 0x24) = (u32)sub_080718F4;
    p38->f24 = 0x08473304;
    sub_08003A6C((s32)p6C + 0x30, 0, 0x08473324);
    {
        u32 off = 0x174C;
        p6C->f4 = *(u32 *)((u8 *)&D_02025FF0 + off);
        off += 4;
        p6C4->f4 = *(u32 *)((u8 *)&D_02025FF0 + off);
    }
    sub_0806D588(p38, p6C4);
    p38->f1C = 0x80000004;
    p38->f0 = D_02025FF0.f18C2;
    p6C4->f1C = 0x60000;
    b = D_080E0C90[*(u32 *)((u8 *)arg0 + 0x7C) & 0x3F];
    p6C->f24 = b;
    p6C->f25 = 0;
    p6C4->f10 = r9;
    sub_080722E0(p6C4, p6C->f24);
    p38->f4 = 0x100;
    p38->f6 = 0x100;
    p38->f8 = r9;
    {
        void *res = sub_08016A2C();
        if (res == NULL) {
            *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = r9;
            sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 3, *D_08671BD0);
            return;
        }
        p6C4->f24 = 0x100;
        p6C4->f40 = (u32)res;
        p6C->f48 = *(u8 *)((u8 *)res + 1);
        *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = r9;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *D_08671BB0);
    }
}
