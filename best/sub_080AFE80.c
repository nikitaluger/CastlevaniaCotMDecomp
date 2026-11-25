struct Elem28 { s32 x; s32 y; };
extern struct Elem28 D_08670228[];

struct S_080AFE80_Obj {
    u8 _0[0x28];
    u32 f28;
    u8 _1[0x3C - 0x2C];
    u32 f3C;
    u8 _2[0x4C - 0x40];
    u8 f4C;
    u8 f50;
    u8 _3[0x5C - 0x51];
    u32 f5C;
};
struct S_080AFE80_A {
    u8 _0[0x38];
    u32 f38;
    u32 f3C;
};
struct S_080AFE80_B {
    u8 _0[2];
    u16 f2;
};
struct S_080AFE80_C {
    u16 f0;
    u8 _0[6];
    u32 f08;
    u32 f0C;
};
struct S_080AFE80_D {
    u8 _0[0x48];
    u32 f48;
};
struct S_080AFE80_E {
    u32 f0;
    u32 f4;
};
struct S_080AFE80_F {
    u8 _0[0x50];
    u8 f50;
    u8 _1[3];
    u8 f54;
    u8 _2[3];
    u8 f58;
    u8 _3[0x5C - 0x59];
    u32 f5C;
    u8 _4[0x6C - 0x60];
    u32 f6C;
    u8 _5[0x7C - 0x70];
    u32 f7C;
};

void sub_080AFE80(struct S_080AFE80_Obj *arg) {
    struct S_080AFE80_D *r4;
    struct S_080AFE80_E *r6;
    struct S_080AFE80_A *a;
    struct S_080AFE80_B *b;
    struct S_080AFE80_C *r7;
    struct S_080AFE80_F *p;
    s32 v, prod;

    r4 = (struct S_080AFE80_D *)arg->f3C;
    r6 = (struct S_080AFE80_E *)((u8 *)r4 + 0x48);
    a = (struct S_080AFE80_A *)arg->f28;
    b = (struct S_080AFE80_B *)a->f38;
    r7 = (struct S_080AFE80_C *)a->f3C;

    ((struct S_080AFE80_F *)r6->f4)->f58 = *((u8 *)arg + 0x4C);
    ((struct S_080AFE80_F *)r4->f48)->f58 = *((u8 *)arg + 0x4C);

    if (b->f2 & 0x10) {
        ((struct S_080AFE80_F *)r4->f48)->f54 = 1;
        p = (struct S_080AFE80_F *)r6->f4;
        v = 1;
    } else {
        ((struct S_080AFE80_F *)r4->f48)->f54 = 0xFF;
        p = (struct S_080AFE80_F *)r6->f4;
        v = -1;
    }
    p->f54 = v;

    p = (struct S_080AFE80_F *)r6->f4;
    p->f7C = *((u8 *)arg + 0x50);
    p = (struct S_080AFE80_F *)r6->f0;
    p->f7C = arg->f5C;

    p = (struct S_080AFE80_F *)r6->f4;
    p->f5C = r7->f08 + ((s32)(s8)p->f54 << 0x12);
    p = (struct S_080AFE80_F *)r6->f4;
    p->f6C = r7->f0C + 0xFFF90000;

    prod = (s32)(s8)((struct S_080AFE80_F *)r4->f48)->f54 *
           D_08670228[*((u8 *)arg + 0x50)].x;
    ((struct S_080AFE80_F *)r4->f48)->f5C =
        ((struct S_080AFE80_F *)r6->f4)->f5C + prod;
    ((struct S_080AFE80_F *)r4->f48)->f6C =
        ((struct S_080AFE80_F *)r6->f4)->f6C +
        D_08670228[*((u8 *)arg + 0x50)].y;

    if (r7->f0 & 1) {
        ((struct S_080AFE80_F *)r6->f4)->f50 = 1;
        ((struct S_080AFE80_F *)r6->f0)->f50 = 1;
    }
}
