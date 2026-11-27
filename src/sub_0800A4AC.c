extern void sub_08005FC4(s32, s32, s32, s32, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C0384(void);
extern s32 gMenuState;

/* Advance one scripted sprite/animation part of an object: clear the part's
 * step counter, run the shared IWRAM animation-step routine on its state
 * (self+0x18/self+0x22), bump the counter, then jump through the frame
 * callback selected by the part's frame byte at self+0x18[part]. If the game
 * isn't in its normal mode yet, first re-apply the shared object settings. */
void sub_0800A4AC(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 *animStep;
    u8 *partState;

    if (gMenuState != 1) {
        sub_08005FC4(0, 1, 3, 0, sub_080C0384);
    }
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    animStep = (s32 *)0x08671BB0;
    partState = self + 0x18;
    sub_080C31E4(partState, self + 0x22, *animStep);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    partState += *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + *(u8 *)partState * 4));
}
