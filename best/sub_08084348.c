struct S_B_43 {
    u8 _0[0x20];
    u16 field20;
    u8 _22[0x2C - 0x22];
    u8 *volatile field2C;
};
struct S_sub_08084348 {
    u8 _0x000[0x24];
    void (*unk24)(void *);
    u8 _0x028[0x38 - 0x28];
    u16 *unk38;
    u8 _0x03C[0x6C - 0x3C];
    u8 *unk6C;
};
struct S_02025FF0_43 {
    u8 _0x000[0x10];
    u32 field10;
    u8 _0x014[0x14ED - 0x14];
    u8 field14ED;
    u8 _0x4EE[0x173A - 0x14EE];
    u8 field173A;
    u8 _0x73B[0x18C2 - 0x173B];
    u16 field18C2;
};
extern struct S_02025FF0_43 gMainWorkspace;

extern s32 sub_0806D518(void *, u16 *, void *);
extern s32 sub_08003740(void *, u16 *);
extern void sub_0806D588(u16 *, void *);
extern void sub_080C31E0(void *, void *);

void sub_08084348(struct S_sub_08084348 *arg0) {
    u8 *r7 = arg0->unk6C;
    struct S_B_43 *r5 = (struct S_B_43 *)(r7 + 4);
    u16 *r6 = arg0->unk38;
    if (sub_0806D518(arg0, r6, r5) == 0) {
        struct S_02025FF0_43 *base = &gMainWorkspace;
        *r6 = base->field18C2;
        if (sub_08003740(r7 + 0x20, r6) == 0) {
            sub_080C31E0(arg0, arg0->unk24);
            return;
        }
        if (r5->field20 == 2) {
            *(u16 *)((u8 *)r5->field2C + 6) = 8;
            *(u16 *)((u8 *)r5->field2C + 8) = 8;
        }
        sub_0806D588(r6, r5);
        if (base->field173A == 0x1C || (base->field14ED == 0 && base->field10 != 0)) {
            sub_080C31E0(arg0, arg0->unk24);
        }
    }
}
