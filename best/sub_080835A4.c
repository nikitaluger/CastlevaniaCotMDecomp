extern s32 sub_0806D450(void *, void *, void *);
extern void sub_08003740(void *, void *);
extern void sub_08005E80(s32);
extern void sub_080C31E0(void *, void *);

struct S_02025FF0_835A4 {
    u8 _00[0x10];
    u32 field10;
    u8 _14[0x14ED - 0x14];
    u8 field14ED;
    u8 _14EE[0x173A - 0x14EE];
    u8 field173A;
    u8 _173B[0x18C2 - 0x173B];
    u16 field18C2;
};
extern struct S_02025FF0_835A4 D_02025FF0;

void sub_080835A4(void *arg0)
{
    u8 *r5 = (u8 *)arg0;
    u8 *r8 = *(u8 **)(r5 + 0x6C);
    u8 *r4 = r8 + 4;
    u8 *r6 = *(u8 **)(r5 + 0x38);

    if (sub_0806D450(r5, r6, r4) <= 0) {
        *(s32 *)(r4 + 0x10) -= 1;
        *(s32 *)(r6 + 0x14) += 0x18000;
        if (*(s32 *)(r4 + 0x10) != 0) {
            goto cont;
        }
    }
    sub_080C31E0(r5, *(void **)(r5 + 0x24));
    return;

cont:
    *(u16 *)(r6 + 0) = D_02025FF0.field18C2;
    sub_08003740(r8 + 0x20, r6);

    *(s32 *)(r4 + 0x14) -= 1;
    if (*(s32 *)(r4 + 0x14) == 0) {
        sub_08005E80(0x162);
        *(s32 *)(r4 + 0x14) = 0x14;
    }

    if (D_02025FF0.field173A == 0x1C ||
        (D_02025FF0.field14ED == 0 && D_02025FF0.field10 != 0)) {
        sub_080C31E0(r5, *(void **)(r5 + 0x24));
    }
}
