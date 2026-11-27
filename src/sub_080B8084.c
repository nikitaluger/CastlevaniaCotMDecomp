extern void sub_080C31E4(void *, void *, s32);
extern void setAnimationFrame(s32, void *, s32, s32);
extern void sub_08011460(s32, void *, s32);

void sub_080B8084(void *arg0) {
    u8 *self = (u8*)arg0;
    s32 v38 = *(s32*)(self + 0x38);
    u8 *p3C = *(u8 **)(self + 0x3C);
    u8 *r4 = p3C + 0x34;
    s32 *lit;
    setAnimationFrame(v38, r4, 6, 0);
    sub_08011460(v38, r4, 0x40000);
    if (*(u8*)r4 & 2) {
        *(u8*)(self + *(s16*)(self + 0x22) * 2 + 0x19) = 0;
        lit = (s32*)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *lit);
    }
}
