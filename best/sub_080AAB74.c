extern s32 sub_080057F8(void);
extern s32 sub_08005820(s32);
extern void sub_080AAB3C(s32, s32, s32);
extern s32 sub_080C31E0(s32, s32);

typedef struct { s32 a, b; } Pair;
typedef struct { Pair p[2]; } Big;
extern Big D_081021B4;
extern s32 D_08671BFC[];

void sub_080AAB74(u8 arg0) {
    Big local = D_081021B4;
    s32 r9 = -1;
    s32 r7;
    s32 t1, t2;
    s32 *pd;
    s32 r5v, r1v;
    u32 mult;

    r7 = sub_08005820(0x800) + 0x7800;
    if (sub_080057F8() & 1) {
        r7 = 0x8000 - r7;
        r9 = 1;
    }
    mult = ((u32)(sub_08005820(0x100000) + 0x2C0000)) >> 8;
    pd = D_08671BFC;
    t1 = sub_080C31E0(r7 + 0x4000, *pd);
    r5v = local.p[arg0].a;
    r5v += (t1 >> 8) * (s32)mult;
    t2 = sub_080C31E0(r7, *pd);
    r1v = local.p[arg0].b + (t2 >> 8) * (s32)mult;
    sub_080AAB3C(r5v, r1v, r9);
}
