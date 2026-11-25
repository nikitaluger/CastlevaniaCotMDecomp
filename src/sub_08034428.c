void sub_0803B220(void *self, void *state, u16 *attr, u8 *frame);

/* Effect-entity tick: forward the attribute word at +0x38 and the work state
 * at +0x3C (with its frame counter at +0x50) to the effect update. */
void sub_08034428(void *self) {
    s32 state;
    s32 attr;
    attr = *(s32 *)((s8 *)self + 0x38);
    state = *(s32 *)((s8 *)self + 0x3C);
    sub_0803B220(self, state, attr, state + 0x50);
}
