struct S_0808154C_arg {
    u8 _0[0x24];
    void *f24;
    s32 f28;
    u8 _2C[0x38 - 0x2C];
    u16 *f38;
    u8 _3C[0x6C - 0x3C];
    void *f6C;
};

struct S_0808154C_sub {
    u8 _0[4];
    s32 f04;
    u8 _08[0x10 - 0x08];
    s32 f10;
    s32 f14;
    u8 _18[4];
    u8 f1C;
};

struct S_02025FF0 {
    u8 _0[0x10];
    u32 f10;
    u8 _14[0x14ED - 0x14];
    u8 f14ED;
    u8 _14EE[0x173A - 0x14EE];
    u8 f173A;
    u8 _173B[0x18C2 - 0x173B];
    u16 f18C2;
};
extern struct S_02025FF0 D_02025FF0;

extern s32 sub_0806D450(void *, u16 *, void *);
extern void *sub_0806D2A0(s32, s32, s32, s32);
extern void sub_08003740(void *, u16 *);
extern void sub_08005E80(s32);
extern void sub_0806D588(u16 *, void *);
extern void sub_080C31E0(void *, void *);

void sub_0808154C(struct S_0808154C_arg *arg) {
    void *p = (u8 *)arg->f6C + 4;
    u16 *p16 = arg->f38;
    struct S_0808154C_sub *sub = p;

    if (sub_0806D450(arg, p16, sub) > 0) {
        sub_080C31E0(arg, arg->f24);
        return;
    }

    sub->f10 = sub->f10 - 1;
    if (sub->f10 > 0xC0) {
        sub->f04 = sub->f04 + 0xFFFF0000;
    }
    if (sub->f10 <= 0x3F) {
        sub->f04 = sub->f04 + 0x10000;
    }
    if ((sub->f10 & 3) == 0) {
        void *res = sub_0806D2A0((s32)arg->f28, 0x6B, 0xA, 0x12);
        if (res != NULL) {
            *(s32 *)((u8 *)res + 0x9C) = sub->f10 >> 2;
        }
    }
    if (sub->f10 == 0) {
        sub_080C31E0(arg, arg->f24);
        return;
    }

    *p16 = D_02025FF0.f18C2;
    sub_08003740(p + 0x1C, p16);
    sub->f14 = sub->f14 - 1;
    if (sub->f14 == 0) {
        sub_08005E80(0x15E);
        sub->f14 = 0x1E;
    }
    sub_0806D588(p16, sub);
    if (D_02025FF0.f173A == 0x1C ||
        (D_02025FF0.f14ED == 0 && D_02025FF0.f10 != 0)) {
        sub_080C31E0(arg, arg->f24);
    }
}
