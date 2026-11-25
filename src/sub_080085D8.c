void sub_080060C4(s32 arg0, s32 arg1, s32 arg2, void (*callback)(void));
void sub_080C0384(void);

struct State {
    u8 pad_0x00[0x04];
    s32 counter;                /* +0x04: broadcast/step counter */
};

/* Advance the state block's counter, then broadcast message 0xC with no
 * payload to every registered callback. */
void sub_080085D8(struct State *state) {
    state->counter = state->counter + 1;
    sub_080060C4(0, 0xC, 0, sub_080C0384);
}
