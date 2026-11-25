extern void sub_0809856C(s32, void *, s32);
extern void sub_080BB984(void *, void *);
extern void sub_080BE740(s8);
extern void sub_080C31E4(void *, void *, s32);

/* Periodically spawns an effect on the subject, updates its facing, scatters a
 * burst on every 0x10-th animation frame, and fires the effect on frame 0xF0. */
void sub_080BA6F0(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *subject = *(u8 **)(self + 0x3C);
    u8 *subjectState = subject + 0x48;
    u8 *partner = *(u8 **)(self + 0x4C);
    sub_0809856C(0x1AC, subject + 0xD4, 0x19);
    sub_080BB984(subject, subjectState);
    if ((*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) & 0x0F) == 0) {
        sub_080BE740((s8)*(s8 *)(partner + 0x35));
    }
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0xF0) {
        s32 *lit;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        lit = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *lit);
    }
}
