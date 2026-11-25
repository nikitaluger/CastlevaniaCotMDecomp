void sub_08098664(void *, s32, s32);
void sub_080988B8(void *, s32);
void sub_080BB940(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* Clears a subject flag, syncs a linked partner to the subject's state and
 * facing, then on a late animation frame forces the partner into state 0. */
void sub_080BA5D4(u8 *self) {
    u8 *subject = (u8 *)*(u32 *)(self + 0x3C);
    u8 *subjectState = subject + 0x48;
    u8 *partner = (u8 *)*(u32 *)(self + 0x4C);
    u8 state;
    s32 *lit;

    *(u32 *)(subject + 0xD4) = 0;
    sub_080BB940(subject, partner);
    if (*(u32 *)(subjectState + 0x64) != 0) {
        sub_080988B8(partner, *(s32 *)(subject + 8));
    }
    if ((u32)*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) > 0x10U) {
        state = *(u8 *)(partner + 0x25);
        if (state == 0) {
            sub_08098664(partner, 3, 0);
            *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = state;
            lit = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *lit);
        }
    }
}
