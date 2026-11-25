extern void *D_08671BB0;
extern void sub_080113A8(void *, void *);
extern void sub_0801165C(void *, s32);
extern void sub_080146D0(void *, s32, s32);
extern s32 sub_080C2F20(s32, s32);
extern void sub_080C31E4(void *, void *, s32);

void sub_08037488(u8 *arg0) {
    u8 *p38;
    u8 *p3C;
    u8 *p34;
    u8 *p48;
    s32 v;
    s32 c100;

    p38 = *(u8 **)(arg0 + 0x38);
    p3C = *(u8 **)(arg0 + 0x3C);
    p34 = p3C + 0x34;
    p48 = p3C + 0x48;
    if (*(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) & 1) {
        *(u16 *)p38 = (*(u16 *)p38 & 0xFFF) | 0xC000;
    } else {
        *(u16 *)p38 = (*(u16 *)p38 & 0xFFF) | ((*(u16 *)(p3C + 0x22) + 8) << 0xC);
    }
    sub_080113A8(p38, p34);
    sub_080146D0(p3C, *(s32 *)(p48 + 4), *(s32 *)p48);
    sub_0801165C(p3C, 0);
    v = *(s32 *)p48 + (s32)0xFFFFD000;
    *(s32 *)p48 = v;
    *(s16 *)(p38 + 4) = (s16)(0x100 - sub_080C2F20(v * 0xFF, 0x40000));
    c100 = 0x100;
    *(s16 *)(p38 + 6) = (s16)(sub_080C2F20(*(s32 *)p48 * 0x500, 0x40000) + c100);
    if (*(s32 *)p48 <= 0) {
        *(s32 *)p48 = 0;
        *(u16 *)p38 = (u16)((*(u16 *)p38 & 0xFFF) | ((*(u16 *)(p3C + 0x22) + 8) << 0xC));
        *(s16 *)(p38 + 4) = c100;
        *(s16 *)(p38 + 6) = c100;
        *(u8 *)(*(u8 **)(p3C + 0x28) + 1) = 1;
        *(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) = 0;
        sub_080C31E4(arg0 + 0x18, arg0 + 0x22, (s32)D_08671BB0);
    }
}
