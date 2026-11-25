void sub_08005E80(u16 songId);

struct State {
    u8 pad_0x00[0x04];
    s32 counter;                /* +0x04: broadcast/step counter */
};

/* Advance the state block's counter, then start sound 0x13. */
void sub_080085C4(struct State *state) {
    state->counter = state->counter + 1;
    sub_08005E80(0x13);
}
