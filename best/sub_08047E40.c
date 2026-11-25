void sub_08011368(void *, void *, s32, s32);
void sub_080C31E8(void *, void *, s32, s32);

struct S_02025FF0_47E40 {
    u8 _0[0x18BC];
    u16 f18BC;
};
extern struct S_02025FF0_47E40 D_02025FF0;

void sub_08047E40(u8 *self) {
    void *p38 = *(void **)(self + 0x38);
    u8 *p3C = *(u8 **)(self + 0x3C);
    u8 *p34 = p3C + 0x34;
    u8 *p48 = p3C + 0x48;
    u8 *p28;
    u32 *lit;
    sub_08011368(p38, p34, 0x0B, 0);
    p28 = *(u8 **)(p3C + 0x28);
    if (*(u16 *)(p28 + 0x14) & 1) {
        *(u16 *)(p48 + 8) = 0x12C;
        *(u16 *)(p48 + 0xA) = 1;
        D_02025FF0.f18BC++;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        lit = (u32 *)0x08671BD0;
        sub_080C31E8(self + 0x18, self + 0x22, 1, *lit);
    } else {
        u32 v = *(u16 *)(p48 + 8) - 1;
        *(u16 *)(p48 + 8) = v;
        if ((s32)(v << 16) < 0) {
            *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
            lit = (u32 *)0x08671BD0;
            sub_080C31E8(self + 0x18, self + 0x22, 2, *lit);
        }
    }
}
