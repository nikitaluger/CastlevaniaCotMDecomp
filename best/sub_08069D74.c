extern s32 sub_0806C4B4(void *, void *);
extern void sub_0806C5EC(void *, void *, void *, void *);
extern s32 sub_08065CC8(void *, void *, void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void sub_080C31E8(void *, void *, s32, u32);
extern u32 D_08671BD8;

struct G {
    u8 _0[0x14ED];
    u8 f14ED;
    u8 _1[0x18C5 - 0x14ED - 1];
    u8 f18C5;
    u8 f18C6;
};
extern struct G D_02025FF0;

void sub_08069D74(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x6C);
    s32 val = *(s32 *)(arg0 + 0x38);
    s32 res;

    res = sub_0806C4B4(obj + 4, obj + 4);
    if (res != 0) return;
    sub_0806C5EC(arg0, (void *)val, obj + 4, obj + 4);
    if (D_02025FF0.f14ED == 0xAA) {
        if (*(u8 *)(obj + 0x12C) != 0) {
            *(u8 *)(arg0 + (u32)(*(s16 *)(arg0 + 0x22)) * 2 + 0x17) = res;
            sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 0x29, D_08671BD8);
        } else {
            *(u8 *)(arg0 + (u32)(*(s16 *)(arg0 + 0x22)) * 2 + 0x17) = res;
            sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 0x24, D_08671BD8);
        }
    } else {
        *(u8 *)(arg0 + (u32)(*(s16 *)(arg0 + 0x22)) * 2 + 0x17) = res;
        sub_080C31E8(arg0 + 0x18, arg0 + 0x22, (u16)sub_08065CC8(arg0, (void *)val, obj + 4, obj + 4), D_08671BD8);
    }
    D_02025FF0.f18C6 = 0;
    D_02025FF0.f18C5 = 0;
    sub_0806C6B0(arg0, (void *)val, obj + 4, obj + 4);
}
