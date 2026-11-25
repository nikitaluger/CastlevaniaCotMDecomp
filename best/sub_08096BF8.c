extern void sub_08011368(u32, u32, s32, s32);
extern s32 sub_08007EA8(s32);
extern void sub_08007E24(s32);
extern void sub_080C31E8(u8 *, u8 *, s32, u32);
extern void sub_080C31E0(u8 *, u32);
extern void sub_08011344(u32, u32, s32, s32);
extern void sub_08005E80(s32);
extern void sub_080C31E4(u8 *, u8 *, u32);
extern u8 D_02025368[];

void sub_08096BF8(u8 *arg0) {
    u32 a38;
    u8 *a3C;
    u8 *flagBase;
    u32 a3C18;
    u8 *flag;
    u8 f;
    s16 val;
    u8 z;
    u8 *p18;
    s16 r7;
    u32 *gBD0;
    u32 *gBB0;

    a38 = *(u32 *)(arg0 + 0x38);
    flagBase = D_02025368;
    a3C = *(u8 **)(arg0 + 0x3C);
    a3C18 = (u32)a3C + 0x18;
    sub_08011368(a38, a3C18, 0, 1);
    flag = flagBase + 0x3CE;
    f = *flag;
    if (f == 0) {
        val = *(s16 *)(a3C + 0x14);
        if (val == 1) {
            *(s16 *)(a3C + 0x14) = f;
            if (sub_08007EA8(0x32) == 0) {
                sub_08007E24(0x32);
                z = 0;
                *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) = z;
                gBD0 = (u32 *)0x08671BD0;
                p18 = arg0 + 0x18;
                sub_080C31E8(p18, arg0 + 0x22, 5, *gBD0);
                *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) += 1;
                p18 += *(s16 *)(arg0 + 0x22) * 2;
                sub_080C31E0(arg0, *(u32 *)(*(u32 *)(arg0 + 0x14) + *(u8 *)p18 * 4));
            }
        }
    } else {
        u8 *a3C2 = *(u8 **)(arg0 + 0x3C);
        r7 = *(s16 *)(a3C2 + 0x14);
        if (r7 == 1) {
            sub_08011344(a38, a3C18, 3, 0);
            z = 0;
            *(s16 *)(a3C + 0x16) = r7;
            sub_08005E80(0x1B7);
            *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) = z;
            gBB0 = (u32 *)0x08671BB0;
            sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *gBB0);
        }
    }
}
