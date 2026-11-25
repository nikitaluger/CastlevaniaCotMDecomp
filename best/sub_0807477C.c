struct S02025FF0_7477C {
    u8 _pad0[0x10];
    u32 f10;
    u8 _pad1[0x14ED - 0x14];
    u8 f14ED;
    u8 _pad2[0x173A - 0x14EE];
    u8 f173A;
    u8 _pad3[0x18C2 - 0x173B];
    u16 f18C2;
};
extern struct S02025FF0_7477C D_02025FF0;

struct R7_7477C {
    u8 _0;
    u8 f1;
    u8 _1[0x0A];
    u32 fC;
    u32 f10;
};

struct P4_7477C {
    u32 f0;
    u32 f4;
    u8 _1[0x10 - 8];
    u32 f10;
    u8 _2[0x2C - 0x14];
    u8 *f2C;
    u8 _3[0x4C - 0x30];
    struct R7_7477C *f4C;
};

struct Inner_7477C {
    u8 _0[0x4];
    u32 f4;
    u8 _1[0x20 - 0x8];
    u8 f20[1];
    u8 _2[0x54 - 0x21];
    u8 f54;
};

struct Arg_7477C {
    u8 _0[0x18];
    u8 f18[1];
    u8 _1[0x22 - 0x19];
    s16 f22;
    u32 f24;
    u8 _2[0x38 - 0x28];
    u16 *f38;
    u8 _3[0x6C - 0x3C];
    struct Inner_7477C *f6C;
};

extern s32 sub_0806D518(void *, u16 *, void *);
extern void sub_08003740(void *);
extern s32 sub_0806D588(u16 *, void *);
extern s32 sub_0806D2F8(void *, u16 *);
extern s32 sub_080C364C(s32, s32);
extern void sub_080C31E0(void *, u32);
extern void sub_080C31E4(void *, void *, s32);

void sub_0807477C(struct Arg_7477C *arg0) {
    struct Inner_7477C *p;
    struct P4_7477C *p4;
    u16 *idx;
    struct S02025FF0_7477C *g;
    struct R7_7477C *r7;
    s32 a, b;

    p = arg0->f6C;
    p4 = (struct P4_7477C *)((u8 *)p + 4);
    idx = arg0->f38;
    if (sub_0806D518(arg0, idx, p4) == 0) {
        g = &D_02025FF0;
        *idx = g->f18C2;
        sub_08003740(p->f20);
        r7 = p4->f4C;
        if ((r7->f1 != p->f54) || (--p4->f10 == 0)) {
            *(p4->f2C + 1) = 0;
            ((u8 *)arg0 + 2 * (s16)arg0->f22)[0x19] = 0;
            {
                void **pp = (void **)0x08671BB0;
                sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, (s32)*pp);
            }
            return;
        }
        b = r7->fC;
        a = p4->f0;
        a += sub_080C364C(b - a, 0x14);
        p4->f0 = a;
        b = r7->f10;
        a = p4->f4;
        a += sub_080C364C(b - a, 0x14);
        p4->f4 = a;
        sub_0806D588(idx, p4);
        if ((g->f173A == 0x1C) || ((g->f14ED == 0) && (g->f10 != 0))) {
            sub_080C31E0(arg0, arg0->f24);
        } else {
            sub_0806D2F8(arg0, idx);
        }
    }
}
