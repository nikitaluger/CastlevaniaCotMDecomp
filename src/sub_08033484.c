s32 sub_0803B220(void *self, s32 state, s32 attr, s32 frame);

/* Start the effect ticker for `self`: pass the state block at +0x3C, the
 * attribute word at +0x38 and the frame counter kept at state+0x50. */
void sub_08033484(void *self) {
    s32 state;
    s32 attr;
    attr = *(s32 *)((s8 *)self + 0x38);
    state = *(s32 *)((s8 *)self + 0x3C);
    sub_0803B220(self, state, attr, state + 0x50);
}
