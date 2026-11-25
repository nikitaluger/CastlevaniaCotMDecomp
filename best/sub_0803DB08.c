extern s32 sub_08005820(s32, s32);
extern s32 sub_08014990(s32);
extern void sub_08011368(s32, void *, u16, u8);
extern void sub_080C31E4(void *, void *, s32);

void sub_0803DB08(void *arg0)
{
    u8 *self = arg0;
    s32 r7;
    u8 *r5;
    u8 *r4;
    s32 v;
    s32 *lit;

    r7 = *(s32 *)(self + 0x38);
    r5 = *(u8 **)(self + 0x3C);
    r4 = r5 + 0x34;
    sub_08011368(r7, r4, 0xD, 0);
    *(s32 *)(r5 + 0x10) = 0;
    if (*(u8 *)r4 & 2) {
        if (sub_08014990(r7) > 0) {
            *(s32 *)(r5 + 0x10) = 0xFFFEA000;
        } else {
            *(s32 *)(r5 + 0x10) = 0x16000;
        }
        v = *(s16 *)(r5 + 0x1C);
        *(s32 *)(r5 + 0x14) = sub_08005820(0x4000, v) + 0xFFFE0000;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        lit = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *lit);
    }
}
